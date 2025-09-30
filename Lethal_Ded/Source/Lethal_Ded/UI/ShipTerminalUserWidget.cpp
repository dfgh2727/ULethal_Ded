// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShipTerminalUserWidget.h"
#include "Global/LCGlobal.h"
#include "Global/Controller/LCPlayerController.h"



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

void UShipTerminalUserWidget::SetTargetRendOrCompany(bool Sign)
{
	Sign = bTargetRendOrCompany;
	// false´Â Rend, true´Â Company
}

bool UShipTerminalUserWidget::CheckTargetRendOrCompany()
{
	return bTargetRendOrCompany;
}

void UShipTerminalUserWidget::SetLCPlayerController(ALCPlayerController* LCPlayerController)
{
	SavedPlayerController = Cast<APlayerController>(LCPlayerController);
}

APlayerController* UShipTerminalUserWidget::GetLCPlayerController()
{
	return SavedPlayerController;
}


void UShipTerminalUserWidget::TurnItOccupied()
{
	bOccupied = true;
}

void UShipTerminalUserWidget::TurnItUnoccupied()
{
	bOccupied = false;
}

bool UShipTerminalUserWidget::CheckOccupied()
{
	return bOccupied;
}
