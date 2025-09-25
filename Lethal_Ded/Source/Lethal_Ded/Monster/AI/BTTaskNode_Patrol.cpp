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
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(AIStateValue)); // 0 �� Idle
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

		// ���� Ʈ���̽�: �� üũ
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

	// ���� �� ������ ��ġ�� ����
	if (MaxDistance > 0.0f)
	{
		PlayAIData.PatrolPos.Add(BestPos);
	}
	else
	{
		// ������ ��ġ�� ������ ���� �ڸ���
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
		Start(_OwnerComp); // ���ο� ���� ã��
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

	// ���� Ʈ���̽�: �� üũ
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
		// ���� ������ ��ȸ: ������ �������� �̵�
		FVector RightDir = FVector::CrossProduct(PatrolDir, FVector::UpVector);
		RightDir.Normalize();
		SelfActor->AddMovementInput(RightDir, 1.0f);
	}
	else
	{
		// ���� ������ ���������� PatrolDir�� �̵�
		SelfActor->AddMovementInput(PatrolDir);
	}

	float Size = (SelfActorPos - TargetPos).Size();

	if (Size <= 100.0f)
	{
		PlayAIData.PatrolPos.RemoveAt(0);
	}
}
