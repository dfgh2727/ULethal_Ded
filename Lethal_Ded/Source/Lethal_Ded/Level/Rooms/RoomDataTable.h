// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RoomDataTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FRoomDataRow : public FTableRowBase
{
    GENERATED_BODY()

    FRoomDataRow() {}
    ~FRoomDataRow() {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class AMasterRoom> RoomList;


};


UCLASS()
class LETHAL_DED_API URoomDataTable : public UObject
{
	GENERATED_BODY()
	
};
