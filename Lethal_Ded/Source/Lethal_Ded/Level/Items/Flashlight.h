// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/Items/Item.h"
#include "Flashlight.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API AFlashlight : public AItem
{
	GENERATED_BODY()

public:
	AFlashlight();

	virtual void Tick(float DeltaTime) override;

	void TurnOnFlashlight()
	{
		bFlash = true;
	}

	void TurnOffFlashlight()
	{
		bFlash = false;
	}

	float GetCurBatteryLevel()
	{
		return curBatteryLevel;
	}
protected:
	virtual void BeginPlay() override;


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level|Item|Flashlight", meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* SpotlightComponent;

	bool bFlash = true;
	bool bBatteryRemained = true;
	float totalBatteryLevel = 140.0f;
	float curBatteryLevel = 0.0f;

};
