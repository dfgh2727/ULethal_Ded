// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_Spawn.h"

#include "Monster/MonsterAnimInstance.h"
#include "Monster/Monster.h"

void UBTTaskNode_Spawn::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(AIStateValue));
	}
}

void UBTTaskNode_Spawn::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);


	if(false == PlayAIData.MonsterAnimInstance->MontageIsPlaying())
	{
		ChangeState(_OwnerComp, EAIState::Idle);
		return;
	}
}

UBTTaskNode_Spawn::UBTTaskNode_Spawn()
{
	AIStateValue = EAIState::Spawn;
}

