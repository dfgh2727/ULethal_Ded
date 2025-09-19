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
	
};
