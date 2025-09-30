// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ShipUserWidget.h"
#include "ShipTerminalUserWidget.generated.h"

class ALCPlayerController;
/**
 * 
 */
UCLASS()
class LETHAL_DED_API UShipTerminalUserWidget : public UShipUserWidget
{
	GENERATED_BODY()

public:
	bool CheckTargetRendOrCompany();

	APlayerController* GetLCPlayerController();
	//(사실 GetPlayerController가 맞으나 함수명이 겹쳐서 LCPlayercontroller로 표기)

	UFUNCTION(BlueprintCallable)
	void SetLCPlayerController(ALCPlayerController* LCPlayerController);
	//터미널 사용시 한번 호출 필요

	UFUNCTION(BlueprintCallable)
	void TurnItOccupied(); // 터미널 사용시 호출

	UFUNCTION(BlueprintCallable)
	void TurnItUnoccupied(); // 터미널 떠날 때 호출

	UFUNCTION(BlueprintCallable)
	bool CheckOccupied(); // 터미널 사용 여부 확인시 호출

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

	UFUNCTION(BlueprintCallable)
	void SetTargetRendOrCompany(bool Sign);

	//UFUNCTION(BlueprintCallable)
	//void OrderTravelToRend(APlayerController* PlayerController);
	//
	//UFUNCTION(BlueprintCallable)
	//void OrderTravelToCompany(APlayerController* PlayerController);
	//
	//UFUNCTION(BlueprintCallable)
	//void OrderTravelToReady(APlayerController* PlayerController);

private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship|Content", meta = (AllowPrivateAccess = "true"))
	//FString Moons = TEXT("Moons");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship|Content", meta = (AllowPrivateAccess = "true"))
	FString UserInputContents = TEXT("Temp");

	UPROPERTY(BlueprintReadWrite, Category = "Ship|Content", meta = (AllowPrivateAccess = "true"))
	bool bAnswer = false;

	UPROPERTY(BlueprintReadWrite, Category = "Ship|Content", meta = (AllowPrivateAccess = "true"))
	bool bConfirm = false;

	UPROPERTY(BlueprintReadWrite, Category = "Ship|Content", meta = (AllowPrivateAccess = "true"))
	bool bTargetRendOrCompany = false;

	bool bOccupied = false;

	APlayerController* SavedPlayerController = nullptr;
	
};
