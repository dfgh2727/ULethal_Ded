// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Controller/LCTitleController.h"

ALCTitleController::ALCTitleController()
{
}

ALCTitleController::~ALCTitleController()
{
}

void ALCTitleController::BeginPlay()
{
	Super::BeginPlay();
}

void ALCTitleController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALCTitleController::SetServerTravel_Implementation(const FString& TargetLevel)
{
	if (HasAuthority())
	{
		GetWorld()->ServerTravel(TargetLevel);
	}
}