// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShipTerminalUserWidget.h"

void UShipTerminalUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

bool UShipTerminalUserWidget::CheckContentMoon(FString content)
{
	if (content == Moons)
	{
		return true;
	}

	return false;
}
