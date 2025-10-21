// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/LCGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Global/DevGlob/GlobDevGameMode.h" // ÀÌ°Å ¹¹Áö??
#include "Global/Controller/LCTitleController.h"
#include "Global/Controller/LCPlayerController.h"
#include "Global/GameMode/ReadyGameMode.h"


ULCGameInstance::ULCGameInstance()
{

}

ULCGameInstance::~ULCGameInstance()
{

}

void ULCGameInstance::CreateRoom(APlayerController* PlayerController)
{
	FString ReadyLevelName = ReadyLevel.GetLongPackageName();
	//FString OpenLevelName = FString::Printf(TEXT("%s:%s%s"), *LocalIP, *Port, *ReadyLevelName);
	FString OpenLevelName = FString::Printf(TEXT("%s:%s"), *LocalIP, *Port);


	ALCTitleController* LCTitleController = Cast<ALCTitleController>(PlayerController);
	if (LCTitleController != nullptr)
	{
		//Debug
		LCTitleController->SetServerTravel(ReadyLevelName);
		UGameplayStatics::OpenLevel(GetWorld(), *OpenLevelName, true);

		//Release
		//UGameplayStatics::OpenLevel(GetWorld(), *OpenLevelName, true);
	}
}

void ULCGameInstance::JoinRoom(FString IP, APlayerController* PlayerController)
{
	FString ReadyLevelName = ReadyLevel.GetLongPackageName();

	FString ConnectLevelName = FString::Printf(TEXT("%s:%s"), *IP, *Port);

	ALCTitleController* LCTitleController = Cast<ALCTitleController>(PlayerController);
	if (LCTitleController != nullptr)
	{
		UGameplayStatics::OpenLevel(GetWorld(), *ConnectLevelName, true);
	}
}

void ULCGameInstance::TravelToRend(APlayerController* PlayerController)
{
	FString PlayLevelName = PlayLevel.GetLongPackageName();

	ALCPlayerController* LCPlayerController = Cast<ALCPlayerController>(PlayerController);
	if (LCPlayerController != nullptr)
	{
		LCPlayerController->SetServerTravel(PlayLevelName);
	}

}

void ULCGameInstance::TravelToCompany(APlayerController* PlayerController)
{
	FString CompanyLevelName = CompanyLevel.GetLongPackageName();

	ALCPlayerController* LCPlayerController = Cast<ALCPlayerController>(PlayerController);
	if (LCPlayerController != nullptr)
	{
		LCPlayerController->SetServerTravel(CompanyLevelName);
	}

}

void ULCGameInstance::TravelToReady(APlayerController* PlayerController)
{
	FString ReadyLevelName = ReadyLevel.GetLongPackageName();
	ALCPlayerController* LCPlayerController = Cast<ALCPlayerController>(PlayerController);
	if (LCPlayerController != nullptr)
	{
		LCPlayerController->SetServerTravel(ReadyLevelName);
	}

}



