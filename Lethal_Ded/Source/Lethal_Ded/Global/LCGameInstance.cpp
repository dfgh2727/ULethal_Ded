// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/LCGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Global/DevGlob/GlobDevGameMode.h"
#include "Global/DevGlob/GlobDevTitleController.h"

ULCGameInstance::ULCGameInstance()
{

}

ULCGameInstance::~ULCGameInstance()
{

}

void ULCGameInstance::CreateRoom(APlayerController* PlayerController)
{
	FString TitleLevelName = TitleLevel.GetLongPackageName();
	FString OpenLevelName = FString::Printf(TEXT(":%s%s"), *Port, *TitleLevelName);

	AGlobDevTitleController* LCPlayerController = Cast<AGlobDevTitleController>(PlayerController);
	if (LCPlayerController != nullptr)
	{
		LCPlayerController->SetServerTravel(TitleLevelName);
	}

	UGameplayStatics::OpenLevel(GetWorld(), *OpenLevelName, true);
}

void ULCGameInstance::JoinRoom(FString IP, APlayerController* PlayerController)
{
	FString TitleLevelName = TitleLevel.GetLongPackageName();
	//FString ConnectLevelName = FString::Printf(TEXT("%s:%s%s"), *IP, *Port, *TitleLevelName);
	FString ConnectLevelName = FString::Printf(TEXT("%s:%s"), *IP, *Port);

	UGameplayStatics::OpenLevel(GetWorld(), FName(*ConnectLevelName), true);

	/*if (PlayerController != nullptr)
	{
		PlayerController->ClientTravel(ConnectLevelName, ETravelType::TRAVEL_Absolute);
	}*/

	AGlobDevTitleController* LCPlayerController = Cast<AGlobDevTitleController>(PlayerController);
	if (LCPlayerController != nullptr)
	{
		LCPlayerController->SetServerTravel(TitleLevelName);
	}
}



