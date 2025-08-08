// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/AI/AIBTTaskNode.h"
#include "BTTaskNode_Attack.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API UBTTaskNode_Attack : public UAIBTTaskNode
{
	GENERATED_BODY()
public:

	void Start(UBehaviorTreeComponent& _OwnerComp);

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

	UBTTaskNode_Attack();
};
