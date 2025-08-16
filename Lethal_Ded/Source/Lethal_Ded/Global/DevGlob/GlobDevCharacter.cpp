// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/DevGlob/GlobDevCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
AGlobDevCharacter::AGlobDevCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGlobDevCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGlobDevCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGlobDevCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGlobDevCharacter::MoveCharacter);

}

void AGlobDevCharacter::MoveCharacter(const FInputActionValue& Value)
{
	FVector InputVector = Value.Get<FVector>();

	InputVector.Normalize();

}

