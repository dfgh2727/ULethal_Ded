// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global/LCEnum.h"
#include "ItemDataTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemDataRow : public FTableRowBase
{
    GENERATED_BODY()

    FItemDataRow() {}
    ~FItemDataRow() {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class AItem> ItemList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int ItemPrice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType GripType = EItemType::ONEHAND;
};




UCLASS()
class LETHAL_DED_API UItemDataTable : public UObject
{
	GENERATED_BODY()
	
};
