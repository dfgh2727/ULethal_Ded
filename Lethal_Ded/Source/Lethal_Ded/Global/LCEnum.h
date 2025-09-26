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
	Spawn UMETA(DisplayName = "생성"),
	Idle UMETA(DisplayName = "대기"),
	Patrol UMETA(DisplayName = "순찰"),
	Trace UMETA(DisplayName = "추적"),
	TraceBack UMETA(DisplayName = "회귀"),
	Attack UMETA(DisplayName = "공격"),
	MAX UMETA(DisplayName = "MAX"),
};

#pragma endregion 


#pragma region LCCharacter
UENUM(BlueprintType)
enum class ECharUpperAnim : uint8
{
	IDLE UMETA(DisplayName = "기본"),
	TWOHANDS UMETA(DisplayName = "두손사용"),
	SHOVEL UMETA(DisplayName = "삽"),
	ATTACKREADY UMETA(DisplayName = "공격준비"),
	ATTACK UMETA(DisplayName = "공격"),
	//FULLATTACK UMETA(DisplayName = "공격전체"),
	MAX UMETA(DisplayName = "MAX"),
};

UENUM(BlueprintType)
enum class ECharLowerAnim : uint8
{
	IDLE UMETA(DisplayName = "기본"),
	WALK UMETA(DisplayName = "걷기"),
	JUMP UMETA(DisplayName = "점프"),
	CROUCH_IDLE UMETA(DisplayName = "앉기기본"),
	CROUCH_WALK UMETA(DisplayName = "앉아걷기"),
	SPRINT UMETA(DisplayName = "달리기"),
	//ATTACK UMETA(DisplayName = "공격"),
	MAX UMETA(DisplayName = "MAX"),
};

#pragma endregion


#pragma region Item
UENUM(BlueprintType)
enum class EItemType : uint8
{
	ONEHAND UMETA(DisplayName = "한손사용"),
	TWOHANDS UMETA(DisplayName = "두손사용"),
};

UENUM(BlueprintType)
enum class EItemInteractType : uint8
{
	NONE UMETA(DisplayName = "없음"),
	WEAPON UMETA(DisplayName = "무기"),
	LIGHT UMETA(DisplayName = "손전등"),
};
#pragma endregion

UCLASS()
class LETHAL_DED_API ULCEnum : public UObject
{
	GENERATED_BODY()
};
