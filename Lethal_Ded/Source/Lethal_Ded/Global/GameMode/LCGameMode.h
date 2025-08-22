// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LCGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API ALCGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	ALCGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
