// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/LCGlobal.h"
#include "Kismet/GameplayStatics.h"
#include "LCGameInstance.h"
#include "Lethal_Ded.h"


ULCGameInstance* ULCGlobal::GetLCGameInstance(const UWorld* World)
{
	return Cast<ULCGameInstance>(UGameplayStatics::GetGameInstance(World));
}

void ULCGlobal::StartServer(UWorld* World, APlayerController* PlayerController)
{
	ULCGlobal::GetLCGameInstance(World)->CreateRoom();

	FString LocalIP = FString::Printf(TEXT("127.0.0.1"));
	ULCGlobal::GetLCGameInstance(World)->JoinRoom(LocalIP, PlayerController);
	//if (true)
	//{
	//	//방이 만들어지면 Client Travel
	//}
	//else
	//{
	//	UE_LOG(LethalCompany_LOG, Warning, TEXT("Creating Room has failed."));
	//}
}

void ULCGlobal::ConnectServer(UWorld* World, APlayerController* PlayerController, FString& IP/*, FString& Port*/)
{
	ULCGlobal::GetLCGameInstance(World)->JoinRoom(IP, PlayerController);
}




