// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LCGlobal.generated.h"

class ULCGameInstance;
/**
 * 
 */
UCLASS()
class LETHAL_DED_API ULCGlobal : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	static ULCGameInstance* GetLCGameInstance(const UWorld* World);

	UFUNCTION(BlueprintCallable)
	static void StartServer(UWorld* World, APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	static void ConnectServer(UWorld* World, APlayerController* PlayerController, FString& IP/*, FString& Port*/);

	UFUNCTION(BlueprintCallable)
	static UWorld* GetWorldPtr(APlayerController* PlayerController);
	
};
