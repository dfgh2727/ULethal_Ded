// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_Idle.h"
#include "Monster/Monster.h"

UBTTaskNode_Idle::UBTTaskNode_Idle()
{
	AIStateValue = EAIState::Idle;
}

void UBTTaskNode_Idle::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(AIStateValue)); // 0 Àº Idle
	}
}

void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.TargetActor)
	{
		ChangeState(_OwnerComp, EAIState::Trace);
		return;
	}

	PlayAIData.CurPatrolTime += _DeltaSeconds;

	if (PlayAIData.CurPatrolTime > PlayAIData.Data.MaxPatrolTime)
	{
		ChangeState(_OwnerComp, EAIState::Patrol);
		return;
	}

	
}
