// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ShipUserWidget.h"
#include "ShipTerminalUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API UShipTerminalUserWidget : public UShipUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	bool CheckContentMoon();

	UFUNCTION(BlueprintCallable)
	bool CheckContentRend();

	UFUNCTION(BlueprintCallable)
	bool CheckContentCompany();

	UFUNCTION(BlueprintCallable)
	void CheckConfirmOrDeny();

	UFUNCTION(BlueprintCallable)
	void ResetBools();

private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship|Content", meta = (AllowPrivateAccess = "true"))
	//FString Moons = TEXT("Moons");
	//FString Rend = TEXT("Rend");
	//FString Confirm = TEXT("Confirm");
	//FString Deny = TEXT("Deny");


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship|Content", meta = (AllowPrivateAccess = "true"))
	FString UserInputContents = TEXT("Temp");

	UPROPERTY(BlueprintReadWrite, Category = "Ship|Content", meta = (AllowPrivateAccess = "true"))
	bool bAnswer = false;

	UPROPERTY(BlueprintReadWrite, Category = "Ship|Content", meta = (AllowPrivateAccess = "true"))
	bool bConfirm = false;
	
};
