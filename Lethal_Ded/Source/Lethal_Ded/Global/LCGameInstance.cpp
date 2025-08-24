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
	FString OpenLevelName = FString::Printf(TEXT("%s:%s%s"), *LocalIP, *Port, *TitleLevelName);

	AGlobDevTitleController* LCPlayerController = Cast<AGlobDevTitleController>(PlayerController);
	if (LCPlayerController != nullptr)
	{
		LCPlayerController->SetServerTravel(TitleLevelName);
	}

	UGameplayStatics::OpenLevel(GetWorld(), *OpenLevelName, true);
	//if (LCPlayerController != nullptr)
	//{
	//	LCPlayerController->SetClientTravel(TitleLevelName);
	//}
}

void ULCGameInstance::JoinRoom(FString IP, APlayerController* PlayerController)
{
	FString TitleLevelName = TitleLevel.GetLongPackageName();
	//FString ConnectLevelName = FString::Printf(TEXT("%s:%s"), *IP, *Port);
	FString ConnectLevelName = FString::Printf(TEXT("%s:%s%s"), *LocalIP, *Port, *TitleLevelName);

	UGameplayStatics::OpenLevel(GetWorld(), *ConnectLevelName, true);

	//AGlobDevTitleController* LCPlayerController = Cast<AGlobDevTitleController>(PlayerController);
	//if (LCPlayerController != nullptr)
	//{
	//	LCPlayerController->SetClientTravel(TitleLevelName);
	//}
}



