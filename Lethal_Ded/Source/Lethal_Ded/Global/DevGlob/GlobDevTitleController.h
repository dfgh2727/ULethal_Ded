// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GlobDevTitleController.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API AGlobDevTitleController : public APlayerController
{
	GENERATED_BODY()

public:

	AGlobDevTitleController();
	~AGlobDevTitleController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable)
	void SetServerTravel(const FString& TargetLevel);
	void SetServerTravel_Implementation(const FString& TargetLevel);


	UFUNCTION(Server, Reliable)
	void SetClientTravel(const FString& TargetLevel);
	void SetClientTravel_Implementation(const FString& TargetLevel);

};
