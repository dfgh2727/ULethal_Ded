// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Monster/MonsterDataTable.h"
#include "AIBTTaskNode.generated.h"


/**
 * 
 */
UCLASS()
class LETHAL_DED_API UAIBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UAIBTTaskNode();

	virtual void Start(UBehaviorTreeComponent& _OwnerComp);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory) override;

	FPlayAIData& GetPlayAIData(UBehaviorTreeComponent& _OwnerComp);

	void ChangeState(UBehaviorTreeComponent& _OwnerComp, EAIState _State);

	void TargetCheck(UBehaviorTreeComponent& _OwnerComp);


protected:
	UPROPERTY(Category = "AI", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EAIState AIStateValue = EAIState::MAX;
};
