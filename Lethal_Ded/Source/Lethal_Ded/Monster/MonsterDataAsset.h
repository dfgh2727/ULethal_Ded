// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MonsterDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FMonsterOption
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString DataKey = "None";
};
UCLASS()
class LETHAL_DED_API UMonsterDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FMonsterOption MonsterOption;
};
