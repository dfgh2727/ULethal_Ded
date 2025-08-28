// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LCCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Character/LCCharacterAnimInstance.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Lethal_Ded/Lethal_Ded.h"


#pragma region LCCharacter_Base
// Sets default values
ALCCharacter::ALCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetMesh()->Mobility = EComponentMobility::Movable;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetMesh(), FName("Neck"));
	CameraComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void ALCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CurUpperAnimType = ECharUpperAnim::IDLE;
	CurLowerAnimType = ECharLowerAnim::IDLE;
}

// Called every frame
void ALCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	ULCCharacterAnimInstance* CharAnimInst = Cast<ULCCharacterAnimInstance>(AnimInst);

	if (nullptr != CharAnimInst)
	{
		CharAnimInst->ChangeAnimation(CurUpperAnimType, CurLowerAnimType);
	}
}

#pragma endregion 


#pragma region LCCharacter_Animation
void ALCCharacter::ChangeAnimation_Server_Implementation(ECharUpperAnim _CurUpperAnimType, ECharLowerAnim _CurLowerAnimType)
{
	ChangeAnimation(_CurUpperAnimType, _CurLowerAnimType);
}

void ALCCharacter::ChangeAnimation_Implementation(ECharUpperAnim _CurUpperAnimType, ECharLowerAnim _CurLowerAnimType)
{
	CurUpperAnimType = _CurUpperAnimType;
	CurLowerAnimType = _CurLowerAnimType;
}

#pragma endregion 


#pragma region LCCharacter_Sync
void ALCCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALCCharacter, CurUpperAnimType);
	DOREPLIFETIME(ALCCharacter, CurLowerAnimType);
	DOREPLIFETIME(ALCCharacter, CurMovementValue);
}

#pragma endregion 


#pragma region LCCharacter_Input
// Called to bind functionality to input
void ALCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ALCCharacter::Rotate);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALCCharacter::Move);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ALCCharacter::Idle);

}

#pragma endregion 


#pragma region LCCharacter_Action
void ALCCharacter::Rotate(const FInputActionValue& _Axis2D)
{
	const FVector2D RotateValue = _Axis2D.Get<FVector2D>();

	if (nullptr != Controller)
	{
		AddControllerYawInput(RotateValue.X);
		AddControllerPitchInput(-RotateValue.Y);
	}
}

void ALCCharacter::Move(const FInputActionValue& _Axis2D)
{
	const FVector2D MovementValue = _Axis2D.Get<FVector2D>();

	SetMovementValue_Server(MovementValue);

	if (nullptr != Controller)
	{
		const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, MovementValue.X);

		const FVector Right = GetActorRightVector();
		AddMovementInput(Right, MovementValue.Y);

		CurLowerAnimType = ECharLowerAnim::WALK;
		CurUpperAnimType = ECharUpperAnim::TWOHANDS;	// Replicated Test
		ChangeAnimation_Server(CurUpperAnimType, CurLowerAnimType);
	}
}

void ALCCharacter::Idle(const struct FInputActionValue& _Axis2D)
{
	const FVector2D MovementValue = _Axis2D.Get<FVector2D>();

	if (nullptr != Controller && true == MovementValue.IsNearlyZero())
	{
		CurLowerAnimType = ECharLowerAnim::IDLE;
		CurUpperAnimType = ECharUpperAnim::IDLE;	// Replicated Test
		ChangeAnimation_Server(CurUpperAnimType, CurLowerAnimType);
	}
}

#pragma endregion 




