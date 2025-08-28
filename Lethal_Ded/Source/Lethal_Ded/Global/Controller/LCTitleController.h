// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LCTitleController.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API ALCTitleController : public APlayerController
{
	GENERATED_BODY()

public:

	ALCTitleController();
	~ALCTitleController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable)
	void SetServerTravel(const FString& TargetLevel);
	void SetServerTravel_Implementation(const FString& TargetLevel);

};
