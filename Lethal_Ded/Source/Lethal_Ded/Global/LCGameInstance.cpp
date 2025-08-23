// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/LCGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Global/DevGlob/GlobDevGameMode.h"

ULCGameInstance::ULCGameInstance()
{

}

ULCGameInstance::~ULCGameInstance()
{

}

void ULCGameInstance::CreateRoom(APlayerController* PlayerController)
{
	FString TitleLevelName = TitleLevel.GetLongPackageName();
	//FString OpenLevelName = FString::Printf(TEXT(":%s%s"), *Port, *TitleLevelName);
	FString ConnectLevelName = FString::Printf(TEXT("%s:%s%s"), *LocalIP, *Port, *TitleLevelName);
	
	AGlobDevGameMode* DevGameMode = Cast<AGlobDevGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	DevGameMode->MakeServerTravel(TitleLevelName);

	if (PlayerController != nullptr)
	{
		PlayerController->ClientTravel(ConnectLevelName, ETravelType::TRAVEL_Absolute);
	}
}

void ULCGameInstance::JoinRoom(FString IP, APlayerController* PlayerController)
{
	FString TitleLevelName = TitleLevel.GetLongPackageName();
	FString ConnectLevelName = FString::Printf(TEXT("%s:%s%s"), *IP, *Port, *TitleLevelName);

	if (PlayerController != nullptr)
	{
		PlayerController->ClientTravel(ConnectLevelName, ETravelType::TRAVEL_Absolute);
	}
}



