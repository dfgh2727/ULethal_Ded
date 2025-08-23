// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Controller/LCPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


void ALCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	SetShowMouseCursor(false);

	PlayerCameraManager->ViewPitchMin = -50.0f;
	PlayerCameraManager->ViewPitchMax = 20.0f;
}

void ALCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//SetupInputComponentEvent();
	if (nullptr != MappingContext)
	{
		AddMappingContext(MappingContext);
	}
}

void ALCPlayerController::AddMappingContext(UInputMappingContext* _MappingContext)
{
	if (nullptr == GetLocalPlayer())
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	InputSystem->ClearAllMappings();
	InputSystem->AddMappingContext(_MappingContext, 0);
}