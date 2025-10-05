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
		AActor* CheckActor = nullptr; // Ÿ������ �ϴ� ���� ����� ����
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), PlayAIData.Data.TargetGroupName, OutActors);

		float CurTargetDis = TNumericLimits<float>::Max();

		// �þ߰�(��) �� �þ߰Ÿ� ����
		const float SightAngle = 90.0f; // ����: 90��
		const float SightRange = PlayAIData.Data.TraceRange;

		FVector SelfLocation = SelfActor->GetActorLocation();
		FVector SelfForward = SelfActor->GetActorForwardVector();

		for (AActor* Actor : OutActors)
		{
			if (Actor == nullptr || Actor == SelfActor)
			{
				continue;
			}

			FVector TargetLocation = Actor->GetActorLocation();
			float TargetDis = (SelfLocation - TargetLocation).Size();

			if (TargetDis < SightRange && TargetDis < CurTargetDis)
			{
				// �þ߰� ���� (dot Ŭ������ NaN ����)
				FVector ToTarget = (TargetLocation - SelfLocation).GetSafeNormal();
				float Dot = FVector::DotProduct(SelfForward, ToTarget);
				Dot = FMath::Clamp(Dot, -1.0f, 1.0f);
				float Angle = FMath::RadiansToDegrees(acosf(Dot));

				if (Angle <= SightAngle * 0.5f)
				{
					// ����Ʈ���̽��� ��ֹ� üũ
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
						// ��ǥ�� ���� LOS�� ������ �� ��ǥ ����
						CheckActor = Actor;
						CurTargetDis = TargetDis;
					}
					else
					{
						// �� �κ��� �ٽ� ����:
						// �� Ÿ���� ���� LOS�� "�ٸ� Ÿ�� �ĺ�"���� ������ �� ���� ���͸� Ÿ������ ä��
						AActor* Blocker = HitResult.GetActor();
						if (IsValid(Blocker) && Blocker != SelfActor && Blocker->ActorHasTag(PlayAIData.Data.TargetGroupName))
						{
							const float BlockerDis = (SelfLocation - Blocker->GetActorLocation()).Size();
							if (BlockerDis < SightRange && BlockerDis < CurTargetDis)
							{
								CheckActor = Blocker;
								CurTargetDis = BlockerDis;
							}
						}
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