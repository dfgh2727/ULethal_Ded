// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_Idle.h"
#include "Monster/Monster.h"

#include "GameFramework/CharacterMovementComponent.h" // �߰�

UBTTaskNode_Idle::UBTTaskNode_Idle()
{
	AIStateValue = EAIState::Idle;
}


// ���� �ڵ� ����
void UBTTaskNode_Idle::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(AIStateValue)); // 0 �� Idle
	}

	ACharacter* Character = Cast<ACharacter>(PlayAIData.SelfPawn);
	if (nullptr != Character)
	{
		//Character->GetCharacterMovement()->bOrientRotationToMovement = true;
		Character->GetCharacterMovement()->MaxWalkSpeed = PlayAIData.Data.MaxSpeed; // ���� �ӵ� ����
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
