// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/AIBTTaskNode.h"
#include <Monster/MonsterDataTable.h>
#include <Global/LCConst.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>


UAIBTTaskNode::UAIBTTaskNode()
{
	bNotifyTick = true;
}

void UAIBTTaskNode::Start(UBehaviorTreeComponent& _OwnerComp)
{

}


EBTNodeResult::Type UAIBTTaskNode::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	if (PlayAIData.AIState != AIStateValue)
	{
		return EBTNodeResult::Type::Failed;
	}

	Start(_OwnerComp);

	return EBTNodeResult::Type::InProgress;
}

FPlayAIData& UAIBTTaskNode::GetPlayAIData(UBehaviorTreeComponent& _OwnerComp)
{
	UObject* Data = _OwnerComp.GetBlackboardComponent()->GetValueAsObject(ULCConst::AI::AIDataName);
	return Cast<UAIDataObject>(Data)->PlayData;
}

void UAIBTTaskNode::ChangeState(UBehaviorTreeComponent& _OwnerComp, EAIState _State)
{
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	PlayAIData.AIState = _State;

	FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
}

void UAIBTTaskNode::TargetCheck(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UAIBTTaskNode::GetPlayAIData(_OwnerComp);

	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;

	if (nullptr == TargetActor)
	{

		AActor* CheckActor = nullptr; // 타깃으로 하는 가장 가까운 액터
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), PlayAIData.Data.TargetGroupName, OutActors);

		float CurTargetDis = TNumericLimits<float>::Max();

		for (AActor * Actor : OutActors)
		{
			float TargetDis = (SelfActor->GetActorLocation() - Actor->GetActorLocation()).Size();
			if (TargetDis < PlayAIData.Data.TraceRange && TargetDis < CurTargetDis)
			{
				CheckActor = Actor;
				CurTargetDis = TargetDis;
			}
		}

		TargetActor = CheckActor;
		if (nullptr != TargetActor)
		{
			PlayAIData.TargetActor = TargetActor;
		}
	}

}

 