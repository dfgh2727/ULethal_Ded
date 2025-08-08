// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_Attack.h"
#include "Monster/Monster.h"

void UBTTaskNode_Attack::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(AIStateValue)); // 0 Àº Idle
	}
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);
	AActor* TargetActor = PlayAIData.TargetActor;

	APawn* SelfActor = PlayAIData.SelfPawn;
	FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();
	SelfActor->SetActorRotation(TargetDir.Rotation());

	if (TargetDir.Size() >= PlayAIData.Data.AttackRange)
	{
		ChangeState(_OwnerComp, EAIState::Idle);
		return;
	}

}

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	AIStateValue = EAIState::Attack;
}
