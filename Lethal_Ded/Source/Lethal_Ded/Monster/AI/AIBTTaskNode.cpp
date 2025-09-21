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

		// 시야각(도) 및 시야거리 설정
		const float SightAngle = 90.0f; // 예시: 90도
		const float SightRange = PlayAIData.Data.TraceRange;

		FVector SelfLocation = SelfActor->GetActorLocation();
		FVector SelfForward = SelfActor->GetActorForwardVector();

		for (AActor* Actor : OutActors)
		{
			FVector TargetLocation = Actor->GetActorLocation();
			float TargetDis = (SelfLocation - TargetLocation).Size();

			if (TargetDis < SightRange && TargetDis < CurTargetDis)
			{
				// 시야각 판정
				FVector ToTarget = (TargetLocation - SelfLocation).GetSafeNormal();
				float Angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(SelfForward, ToTarget)));

				if (Angle <= SightAngle * 0.5f)
				{
					// 라인트레이스로 장애물 체크
					FHitResult HitResult;
					FCollisionQueryParams Params;
					Params.AddIgnoredActor(SelfActor);

					bool bHit = GetWorld()->LineTraceSingleByChannel(
						HitResult,
						SelfLocation,
						TargetLocation,
						ECC_Visibility,
						Params
					);

					if (!bHit || HitResult.GetActor() == Actor)
					{
						CheckActor = Actor;
						CurTargetDis = TargetDis;
					}
				}
			}
		}

		TargetActor = CheckActor;
		if (nullptr != TargetActor)
		{
			PlayAIData.TargetActor = TargetActor;
		}
	}
}

 