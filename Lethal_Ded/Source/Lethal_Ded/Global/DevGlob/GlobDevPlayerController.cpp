// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/DevGlob/GlobDevPlayerController.h"

#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AGlobDevPlayerController::AGlobDevPlayerController()
{
}

AGlobDevPlayerController::~AGlobDevPlayerController()
{
}

void AGlobDevPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnly;
	SetInputMode(GameOnly);

	UEnhancedInputLocalPlayerSubsystem* InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (InputLocalPlayerSubsystem != nullptr)
	{
		InputLocalPlayerSubsystem->AddMappingContext(MappingContext, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
}

void AGlobDevPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGlobDevPlayerController::SetupInputComponent()
{

}

void AGlobDevPlayerController::OnPossess(APawn* ThePawn)
{
	Super::OnPossess(ThePawn);
}
