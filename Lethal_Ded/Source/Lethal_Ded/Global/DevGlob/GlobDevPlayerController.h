// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"

#include "GlobDevPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API AGlobDevPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGlobDevPlayerController();
	~AGlobDevPlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* ThePawn) override;


	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|PlayerController", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext = nullptr;
};
