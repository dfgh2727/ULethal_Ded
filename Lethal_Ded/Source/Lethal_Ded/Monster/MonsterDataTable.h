// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Global/LCEnum.h>
#include "MonsterDataTable.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct FAIData
{
	GENERATED_BODY()
	FAIData() {}
	~FAIData() {}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	double MaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	double TraceRange = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	double PatrolRange = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	double MaxPatrolTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	double AttackRange = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName TargetGroupName = TEXT("None");
};

USTRUCT(BlueprintType)
struct FPlayAIData
{
	GENERATED_BODY()

	FPlayAIData() {}
	~FPlayAIData() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FAIData Data;

	EAIState AIState = EAIState::Spawn;
	double CurHP = 100;
	class APawn* SelfPawn = nullptr;
	AActor* TargetActor = nullptr;

	FVector OriginPos;

	double CurPatrolTime = 0.0f;
	TArray<FVector> PatrolPos;

	class AMonster* SelfAnimPawn = nullptr;
	class UMonsterAnimInstance* MonsterAnimInstance = nullptr;
};

UCLASS(BlueprintType)
class UAIDataObject : public UObject
{
	GENERATED_BODY()

	UAIDataObject() {}
	~UAIDataObject() {}

public:
	FPlayAIData PlayData;
};



USTRUCT(BlueprintType)
struct FMonsterDataRow : public FTableRowBase
{
	GENERATED_BODY()

	FMonsterDataRow() {}
	~FMonsterDataRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FAIData AIData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UBehaviorTree* BTAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class USkeletalMesh* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TMap<EAIState, UAnimMontage*> Animations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<UAnimInstance> AnimationBluePrint;

	
};

UCLASS()
class LETHAL_DED_API UMonsterDataTable : public UObject
{
	GENERATED_BODY()
	
};
