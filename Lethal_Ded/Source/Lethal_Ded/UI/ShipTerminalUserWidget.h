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
	//(��� GetPlayerController�� ������ �Լ����� ���ļ� LCPlayercontroller�� ǥ��)

	UFUNCTION(BlueprintCallable)
	void SetLCPlayerController(ALCPlayerController* LCPlayerController);
	//�͹̳� ���� �ѹ� ȣ�� �ʿ�

	UFUNCTION(BlueprintCallable)
	void TurnItOccupied(); // �͹̳� ���� ȣ��

	UFUNCTION(BlueprintCallable)
	void TurnItUnoccupied(); // �͹̳� ���� �� ȣ��

	UFUNCTION(BlueprintCallable)
	bool CheckOccupied(); // �͹̳� ��� ���� Ȯ�ν� ȣ��

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
