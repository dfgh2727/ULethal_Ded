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
    FString ItemName = "NONE";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int ItemPrice = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType GripType = EItemType::ONEHAND;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemInteractType Interact = EItemInteractType::NONE;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bSwamItem = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector ItemPosition = {0.0f, 0.0f, 0.0f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector ItemRoatation = { 0.0f, 0.0f, 0.0f };

};




UCLASS()
class LETHAL_DED_API UItemDataTable : public UObject
{
	GENERATED_BODY()
	
};
