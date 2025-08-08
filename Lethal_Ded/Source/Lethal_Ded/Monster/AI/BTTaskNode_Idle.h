// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/AI/AIBTTaskNode.h"
#include "BTTaskNode_Idle.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API UBTTaskNode_Idle : public UAIBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_Idle();

	void Start(UBehaviorTreeComponent& _OwnerComp) override;

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;
};
