// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LCEnum.generated.h"

/**
 * 
 */

#pragma region Minha AIState
UENUM(BlueprintType)
enum class EAIState : uint8
{
	Spawn UMETA(DisplayName = "����"),
	Idle UMETA(DisplayName = "���"),
	Patrol UMETA(DisplayName = "����"),
	Trace UMETA(DisplayName = "����"),
	TraceBack UMETA(DisplayName = "ȸ��"),
	Attack UMETA(DisplayName = "����"),
	MAX UMETA(DisplayName = "MAX"),
};

#pragma endregion 


UCLASS()
class LETHAL_DED_API ULCEnum : public UObject
{
	GENERATED_BODY()
};
