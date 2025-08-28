// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/DevGlob/GlobDevTitleController.h"

#include "Kismet/GameplayStatics.h"
#include "Global/GameMode/LCGameMode.h"

AGlobDevTitleController::AGlobDevTitleController()
{
}

AGlobDevTitleController::~AGlobDevTitleController()
{
}

void AGlobDevTitleController::BeginPlay()
{
	Super::BeginPlay();
}

void AGlobDevTitleController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGlobDevTitleController::SetServerTravel_Implementation(const FString& TargetLevel)
{
	//ALCGameMode* LCGameMode = Cast<ALCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (HasAuthority())
	{
		GetWorld()->ServerTravel(TargetLevel);
	}
}

void AGlobDevTitleController::SetClientTravel_Implementation(const FString& TargetLevel)
{
	if (HasAuthority())
	{
		ClientTravel(TargetLevel, ETravelType::TRAVEL_Absolute);
	}
}
