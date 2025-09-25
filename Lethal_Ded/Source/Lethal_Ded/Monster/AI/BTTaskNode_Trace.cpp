// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_Trace.h"
#include "Monster/AI/AIBTTaskNode.h"
#include "Monster/Monster.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTaskNode_Trace::UBTTaskNode_Trace()
{
	AIStateValue = EAIState::Trace;
}


void UBTTaskNode_Trace::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(AIStateValue)); // 0 Àº Idle
	}

	ACharacter* Character = Cast<ACharacter>(PlayAIData.SelfPawn);
	if (nullptr != Character)
	{
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;

		float Speed= Character->GetCharacterMovement()->MaxWalkSpeed * 1.5;
		Character->GetCharacterMovement()->MaxWalkSpeed = Speed;
		
	}

}

void UBTTaskNode_Trace::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (PlayAIData.AIState != AIStateValue)
	{
		return;
	}

	AActor* TargetActor = PlayAIData.TargetActor;

	APawn* SelfActor = PlayAIData.SelfPawn;


	FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();

	double T = TargetDir.Size();


	if (TargetDir.Size() <= PlayAIData.Data.AttackRange)
	{
		ACharacter* Character = Cast<ACharacter>(PlayAIData.SelfPawn);
		if (nullptr != Character)
		{

			float Speed = (float)PlayAIData.Data.MaxSpeed;
			Character->GetCharacterMovement()->MaxWalkSpeed = Speed;

		}
		ChangeState(_OwnerComp, EAIState::Attack);
		return;
	}
	if (PlayAIData.AIState != AIStateValue)
	{
		return;
	}

	if (nullptr == TargetActor)
	{
	

		ACharacter* Character = Cast<ACharacter>(PlayAIData.SelfPawn);
		if (nullptr != Character)
		{

			float Speed = (float)PlayAIData.Data.MaxSpeed;
			Character->GetCharacterMovement()->MaxWalkSpeed = Speed;

		}
		ChangeState(_OwnerComp, EAIState::TraceBack);
		return;
	}
	
	

	SelfActor->AddMovementInput(TargetDir);
	if (TargetDir.Size() >= PlayAIData.Data.TraceRange)
	{
		ACharacter* Character = Cast<ACharacter>(PlayAIData.SelfPawn);
		if (nullptr != Character)
		{

			float Speed = (float)PlayAIData.Data.MaxSpeed;
			Character->GetCharacterMovement()->MaxWalkSpeed = Speed;

		}
		ChangeState(_OwnerComp, EAIState::TraceBack);
		return;
	}


}