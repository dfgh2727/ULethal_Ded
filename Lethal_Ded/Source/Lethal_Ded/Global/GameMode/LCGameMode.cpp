// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GameMode/LCGameMode.h"

ALCGameMode::ALCGameMode()
{
}

void ALCGameMode::BeginPlay()
{
	Super::BeginPlay();

	bUseSeamlessTravel = true; 
}

void ALCGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
