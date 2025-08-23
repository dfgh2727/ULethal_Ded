// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/LCGameInstance.h"
#include "Kismet/GameplayStatics.h"

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
	
	UWorld* World = GetWorld();

	/*if(World != nullptr && HasAuthority)
	{
		World->ServerTravel(TitleLevelName);
	}*/
	//UGameplayStatics::OpenLevel(GetWorld(), *OpenLevelName/*, true, TEXT("listen")*/);
	// 서버 권한이 있는 곳에서 ServerTravel 필요

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



