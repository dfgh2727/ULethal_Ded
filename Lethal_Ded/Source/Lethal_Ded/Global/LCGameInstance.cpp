// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/LCGameInstance.h"
#include "Kismet/GameplayStatics.h"

ULCGameInstance::ULCGameInstance()
{

}

ULCGameInstance::~ULCGameInstance()
{

}

void ULCGameInstance::CreateRoom()
{
	FString TitleLevelName = TitleLevel.GetLongPackageName();
	FString OpenLevelName = FString::Printf(TEXT(":%s%s"), *Port, *TitleLevelName);
	UGameplayStatics::OpenLevel(GetWorld(), *OpenLevelName/*, true, TEXT("listen")*/);
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



