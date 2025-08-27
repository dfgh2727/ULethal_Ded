// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/LCGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Global/DevGlob/GlobDevGameMode.h"
#include "Global/Controller/LCTitleController.h"

ULCGameInstance::ULCGameInstance()
{

}

ULCGameInstance::~ULCGameInstance()
{

}

void ULCGameInstance::CreateRoom(APlayerController* PlayerController)
{
	FString TitleLevelName = TitleLevel.GetLongPackageName();
	FString OpenLevelName = FString::Printf(TEXT("%s:%s%s"), *LocalIP, *Port, *TitleLevelName);

	ALCTitleController* LCTitleController = Cast<ALCTitleController>(PlayerController);
	if (LCTitleController != nullptr)
	{
		LCTitleController->SetServerTravel(TitleLevelName);
	}

	UGameplayStatics::OpenLevel(GetWorld(), *OpenLevelName, true);
}

void ULCGameInstance::JoinRoom(FString IP, APlayerController* PlayerController)
{
	FString TitleLevelName = TitleLevel.GetLongPackageName();

	//아래는 테스트용 ConnectLevelName
	//FString ConnectLevelName = FString::Printf(TEXT("%s:%s%s"), *LocalIP, *Port, *TitleLevelName);

	FString ConnectLevelName = FString::Printf(TEXT("%s:%s%s"), *IP, *Port, *TitleLevelName);

	UGameplayStatics::OpenLevel(GetWorld(), *ConnectLevelName, true);
}



