// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_Die.h"
#include "Monster/AI/AIBTTaskNode.h"
#include "Monster/Monster.h"


UBTTaskNode_Die::UBTTaskNode_Die()
{
	AIStateValue = EAIState::Die;
}


void UBTTaskNode_Die::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(AIStateValue)); // 0 Àº Idle
	}
}

void UBTTaskNode_Die::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
}
