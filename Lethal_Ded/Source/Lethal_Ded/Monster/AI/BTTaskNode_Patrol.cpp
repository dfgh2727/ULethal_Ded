// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_Patrol.h"
#include "BTTaskNode_Patrol.h"
#include "Monster/AI/AIBTTaskNode.h"
#include "Monster/Monster.h"
#include "GameFramework/CharacterMovementComponent.h" // Add this include to resolve the incomplete type erro


UBTTaskNode_Patrol::UBTTaskNode_Patrol()
{
	AIStateValue = EAIState::Patrol;
}
void UBTTaskNode_Patrol::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(AIStateValue)); // 0 은 Idle
	}

	ACharacter* Character = Cast<ACharacter>(PlayAIData.SelfPawn);
	if (nullptr != Character)
	{
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	}

	FRandomStream Stream;
	Stream.GenerateNewSeed();
	FVector Orgin2D = PlayAIData.OriginPos;
	Orgin2D.Z = 0.0f;

	PlayAIData.PatrolPos.Empty();

	float PatrolRange = PlayAIData.Data.PatrolRange;
	int32 MaxTry = 30;
	float MaxDistance = 0.0f;
	FVector BestPos = Orgin2D;

	for (int32 i = 0; i < MaxTry; ++i)
	{
		FVector Dir2D = Stream.GetUnitVector();
		Dir2D.Z = 0.0f;
		FVector CandidatePos = Orgin2D + (Dir2D * PatrolRange);

		// 레이 트레이스: 벽 체크
		FHitResult HitResult;
		FVector TraceStart = Orgin2D;
		FVector TraceEnd = CandidatePos;
		TraceEnd.Z = TraceStart.Z;

		FCollisionQueryParams TraceParams(FName(TEXT("PatrolStartTrace")), true, PlayAIData.SelfPawn);

		bool bHit = PlayAIData.SelfPawn->GetWorld()->LineTraceSingleByChannel(
			HitResult,
			TraceStart,
			TraceEnd,
			ECC_Visibility,
			TraceParams
		);

		if (!bHit || !HitResult.bBlockingHit)
		{
			float Dist = (CandidatePos - Orgin2D).Size();
			if (Dist > MaxDistance)
			{
				MaxDistance = Dist;
				BestPos = CandidatePos;
			}
		}
	}

	// 가장 먼 안전한 위치만 저장
	if (MaxDistance > 0.0f)
	{
		PlayAIData.PatrolPos.Add(BestPos);
	}
	else
	{
		// 안전한 위치가 없으면 원래 자리로
		PlayAIData.PatrolPos.Add(Orgin2D);
	}
}

void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (PlayAIData.PatrolPos.IsEmpty())
	{
		PlayAIData.CurPatrolTime = 0.0f;
		Start(_OwnerComp); // 새로운 방향 찾기
		return;
	}

	TargetCheck(_OwnerComp);

	if (nullptr != PlayAIData.TargetActor)
	{
		ChangeState(_OwnerComp, EAIState::Trace);
		return;
	}

	APawn* SelfActor = PlayAIData.SelfPawn;
	FVector SelfActorPos = SelfActor->GetActorLocation();
	SelfActorPos.Z = 0.0f;

	FVector TargetPos = PlayAIData.PatrolPos[0];
	FVector PatrolDir = (TargetPos - SelfActorPos);
	PatrolDir.Normalize();

	// 레이 트레이스: 벽 체크
	FHitResult HitResult;
	FVector TraceStart = SelfActor->GetActorLocation();
	FVector TraceEnd = TargetPos;
	TraceEnd.Z = TraceStart.Z;

	FCollisionQueryParams TraceParams(FName(TEXT("PatrolTrace")), true, SelfActor);

	bool bHit = SelfActor->GetWorld()->LineTraceSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		TraceParams
	);

	if (bHit && HitResult.bBlockingHit)
	{
		// 벽이 있으면 우회: 오른쪽 방향으로 이동
		FVector RightDir = FVector::CrossProduct(PatrolDir, FVector::UpVector);
		RightDir.Normalize();
		SelfActor->AddMovementInput(RightDir, 1.0f);
	}
	else
	{
		// 벽이 없으면 정상적으로 PatrolDir로 이동
		SelfActor->AddMovementInput(PatrolDir);
	}

	float Size = (SelfActorPos - TargetPos).Size();

	if (Size <= 100.0f)
	{
		PlayAIData.PatrolPos.RemoveAt(0);
	}
}
