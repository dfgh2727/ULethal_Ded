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

	ChangeAnimation_Server(CurUpperAnimType, CurLowerAnimType);

	bIsCrouch = GetCharacterMovement()->bWantsToCrouch;
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
	DOREPLIFETIME(ALCCharacter, bIsFalling);
	DOREPLIFETIME(ALCCharacter, bIsMoving);
	DOREPLIFETIME(ALCCharacter, bIsCrouch);
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
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ALCCharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ALCCharacter::StopJumping);
	//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ALCCharacter::Crouch, bIsCrouch);
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
	bIsMoving = true;

	const FVector2D MovementValue = _Axis2D.Get<FVector2D>();

	SetMovementValue_Server(MovementValue);

	if (nullptr != Controller)
	{
		const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, MovementValue.X);

		const FVector Right = GetActorRightVector();
		AddMovementInput(Right, MovementValue.Y);

		if (false == bIsFalling && true == GetVelocity().IsNearlyZero(10.0f))
		{
			if (false == bIsCrouch)
			{
				CurLowerAnimType = ECharLowerAnim::WALK;
				CurUpperAnimType = ECharUpperAnim::TWOHANDS;	// Replicated Tests
			}
			else
			{
				CurLowerAnimType = ECharLowerAnim::CROUCH_WALK;
			}
		}
	}
}

void ALCCharacter::Idle(const struct FInputActionValue& _Axis2D)
{
	bIsMoving = false;
	//bIsCrouch = false;

	const FVector2D MovementValue = _Axis2D.Get<FVector2D>();


	if (false == bIsCrouch)
	{
		if (nullptr != Controller && true == MovementValue.IsNearlyZero())
		{
			CurLowerAnimType = ECharLowerAnim::IDLE;
			CurUpperAnimType = ECharUpperAnim::IDLE;	// Replicated Test
		}
	}
	else
	{
		if (nullptr != Controller && true == MovementValue.IsNearlyZero())
		{
			CurLowerAnimType = ECharLowerAnim::CROUCH_IDLE;
		}
	}
}

void ALCCharacter::Jump()
{
	if (true == bIsCrouch)
	{
		return;
	}

	Super::Jump();

	CurLowerAnimType = ECharLowerAnim::JUMP;
}

void ALCCharacter::StopJumping()
{
	if (true == bIsCrouch)
	{
		return;
	}

	Super::StopJumping();

	if (false == bIsMoving)
	{
		CurLowerAnimType = ECharLowerAnim::IDLE;
	}
	else
	{
		CurLowerAnimType = ECharLowerAnim::WALK;
	}
}

void ALCCharacter::Crouch(bool _IsCrouch)
{
	Super::Crouch(_IsCrouch);

	CurLowerAnimType = ECharLowerAnim::CROUCH_IDLE;
}

void ALCCharacter::UnCrouch(bool _IsCrouch)
{
	Super::UnCrouch(_IsCrouch);

	CurLowerAnimType = ECharLowerAnim::IDLE;
}

#pragma endregion 




