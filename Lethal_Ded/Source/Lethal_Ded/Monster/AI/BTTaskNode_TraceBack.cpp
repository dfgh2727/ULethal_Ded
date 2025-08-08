// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_TraceBack.h"
#include "Monster/Monster.h"
#include "GameFramework/CharacterMovementComponent.h"


void UBTTaskNode_TraceBack::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(AIStateValue)); // 0 Àº Idle
	}
}

void UBTTaskNode_TraceBack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	APawn* SelfActor = PlayAIData.SelfPawn;

	/*if (nullptr != PlayAIData.TargetActor)
	{
		FVector LookDir = PlayAIData.TargetActor->GetActorLocation() - SelfActor->GetActorLocation();
		SelfActor->SetActorRotation(LookDir.Rotation());
	}*/
	FVector TargetDir = PlayAIData.OriginPos - SelfActor->GetActorLocation();
	SelfActor->AddMovementInput(TargetDir);

	if (TargetDir.Size() < 50.0f)
	{
		ACharacter* Character = Cast<ACharacter>(PlayAIData.SelfPawn);
		if (nullptr != Character)
		{
			Character->GetCharacterMovement()->bOrientRotationToMovement = true;
		}
		PlayAIData.TargetActor = nullptr;
		PlayAIData.CurPatrolTime = 0.0f;
		ChangeState(_OwnerComp, EAIState::Idle);
		return;
	}


}

UBTTaskNode_TraceBack::UBTTaskNode_TraceBack()
{
	AIStateValue = EAIState::TraceBack;
}
