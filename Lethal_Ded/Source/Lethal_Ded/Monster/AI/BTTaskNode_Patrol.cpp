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

	for (size_t i = 0; i < 3; i++)
	{
		FVector Dir2D = Stream.GetUnitVector();
		Dir2D.Z = 0.0f;
		PlayAIData.PatrolPos.Add(Orgin2D + (Dir2D * PlayAIData.Data.PatrolRange));
	}

	// 최후에는 결국 다시 원래자리로 돌아가야 한다.
	PlayAIData.PatrolPos.Add(Orgin2D);
}

void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (true == PlayAIData.PatrolPos.IsEmpty())
	{
		PlayAIData.CurPatrolTime = 0.0f;
		ChangeState(_OwnerComp, EAIState::Idle);
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

	FVector PatrolDir = (PlayAIData.PatrolPos[0] - SelfActorPos);
	PatrolDir.Normalize();

	SelfActor->AddMovementInput(PatrolDir);

	float Size = (SelfActorPos - PlayAIData.PatrolPos[0]).Size();

	if (Size <= 30.0f)
	{
		PlayAIData.PatrolPos.RemoveAt(0);
	}
}
