// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LCGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API ULCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	ULCGameInstance();
	~ULCGameInstance();

	void CreateRoom();
	void JoinRoom(FString IP, APlayerController* PlayerController);

	bool CheckBootingScreenPlayed()
	{
		return bBootingScreenPlayed;
	}

private:

	UPROPERTY(EditAnywhere, Category = "Level")
	TSoftObjectPtr<UWorld> TitleLevel;

	UPROPERTY(EditAnywhere, Category = "Level")
	TSoftObjectPtr<UWorld> PlayLevel;

	UPROPERTY(EditAnywhere, Category = "Num")
	FString Port = TEXT("7777");

	bool bBootingScreenPlayed = false;
	
	
	
};
