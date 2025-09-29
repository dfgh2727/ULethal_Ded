// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShipTerminalUserWidget.h"
#include "Global/LCGlobal.h"
//#include "Global/Controller/LCPlayerController.h"


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

//void UShipTerminalUserWidget::OrderTravelToRend(APlayerController* PlayerController)
//{
//	if (PlayerController != nullptr)
//	{
//		ULCGlobal::SendToRend(GetWorld(), PlayerController);
//	}
//}
//
//void UShipTerminalUserWidget::OrderTravelToCompany(APlayerController* PlayerController)
//{
//	if (PlayerController != nullptr)
//	{
//		ULCGlobal::SendToCompany(GetWorld(), PlayerController);
//	}
//}
//
//void UShipTerminalUserWidget::OrderTravelToReady(APlayerController* PlayerController)
//{
//	if (PlayerController != nullptr)
//	{
//		ULCGlobal::SendToReady(GetWorld(), PlayerController);
//	}
//}
//