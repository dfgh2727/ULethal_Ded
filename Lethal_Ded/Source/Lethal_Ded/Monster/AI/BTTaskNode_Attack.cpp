// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_Attack.h"
#include "Monster/Monster.h"
#include "Net/UnrealNetwork.h" 


void UBTTaskNode_Attack::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(AIStateValue)); // 0 Àº Idle
	}

	PlayAIData.SelfAnimPawn->S2C_ApplyCaptured(PlayAIData.TargetActor,true);
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);
	
	if (PlayAIData.AIState != AIStateValue)
	{
		return;
	}
	AActor* TargetActor = PlayAIData.TargetActor;

	APawn* SelfActor = PlayAIData.SelfPawn;



	{
		AMonster* Owner = Cast<AMonster>(SelfActor);

		if (Owner)
		{
			if (true == Owner->bIsWaitTime)
			{

				PlayAIData.TargetActor->Destroy();
				PlayAIData.TargetActor = nullptr;
				PlayAIData.CurPatrolTime = 0.0f;
				ChangeState(_OwnerComp, EAIState::Idle);
				return;
			}
		}
	}

	

	const FName SocketName = TEXT("PlayerPointSocket");

	FVector SelfLoc = Cast<ACharacter>(SelfActor)->GetMesh()->GetSocketLocation(SocketName);
	

	FVector TargetDir = TargetActor->GetActorLocation() - SelfLoc;
	//SelfActor->SetActorRotation(TargetDir.Rotation());

	double T= TargetDir.Size();

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




