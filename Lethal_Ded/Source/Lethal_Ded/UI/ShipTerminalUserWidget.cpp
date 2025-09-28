// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShipTerminalUserWidget.h"

void UShipTerminalUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

bool UShipTerminalUserWidget::CheckContentMoon()
{
	if (UserInputContents == TEXT("Moons"))
	{
		return true;
	}
	return false;
}

bool UShipTerminalUserWidget::CheckContentRend()
{
	if (UserInputContents == TEXT("Rend"))
	{
		return true;
	}
	return false;
}

bool UShipTerminalUserWidget::CheckContentCompany()
{
	if (UserInputContents == TEXT("Company"))
	{
		return true;
	}

	return false;
}

void UShipTerminalUserWidget::CheckConfirmOrDeny()
{
	if (UserInputContents == TEXT("Confirm"))
	{
		bAnswer = true;
		bConfirm = true;
	}
	else if (UserInputContents == TEXT("Deny"))
	{
		bAnswer = true;
	}
}

void UShipTerminalUserWidget::ResetBools()
{
	bAnswer = false;
	bConfirm = false;
}
