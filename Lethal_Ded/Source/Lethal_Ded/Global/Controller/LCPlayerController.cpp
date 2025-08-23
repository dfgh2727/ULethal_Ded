// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Controller/LCPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


ALCPlayerController::ALCPlayerController()
{
}

void ALCPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ALCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	SetupInputComponentEvent();
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

