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

	bIsFalling = GetCharacterMovement()->IsFalling();
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
	DOREPLIFETIME(ALCCharacter, bIsMoving);
	DOREPLIFETIME(ALCCharacter, bIsFalling);
	DOREPLIFETIME(ALCCharacter, bIsCrouch);
	DOREPLIFETIME(ALCCharacter, bIsSprint);
}

#pragma endregion 


#pragma region LCCharacter_Input
// Called to bind functionality to input
void ALCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ALCCharacter::Rotate);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ALCCharacter::Idle);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALCCharacter::Move);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ALCCharacter::Jump);
	//EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ALCCharacter::Sprint);
	//EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ALCCharacter::Sprint);
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

void ALCCharacter::Idle(const struct FInputActionValue& _Axis2D)
{
	bIsMoving = false;

	const FVector2D MovementValue = _Axis2D.Get<FVector2D>();

	if (nullptr != Controller && true == MovementValue.IsNearlyZero(0.0f))
	{
		UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::IDLE"), *FString(__FUNCSIG__));

		CurUpperAnimType = ECharUpperAnim::IDLE;	// Replicated Test
		CurLowerAnimType = ECharLowerAnim::IDLE;
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

		if (false == bIsFalling && true == GetVelocity().IsNearlyZero(2.0f))
		{
			UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::WALK"), *FString(__FUNCSIG__));

			CurUpperAnimType = ECharUpperAnim::TWOHANDS;	// Replicated Tests
			CurLowerAnimType = ECharLowerAnim::WALK;
		}
	}
}

void ALCCharacter::Jump()
{
	Super::Jump();

	if (GetVelocity().ZAxisVector.IsNearlyZero(2.0f))
	{
		UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::JUMP"), *FString(__FUNCSIG__));

		CurLowerAnimType = ECharLowerAnim::JUMP;
	}

	if (false == bIsMoving)
	{
		UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::IDLE"), *FString(__FUNCSIG__));

		CurLowerAnimType = ECharLowerAnim::IDLE;
	}
	else
	{
		UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::WALK"), *FString(__FUNCSIG__));

		CurLowerAnimType = ECharLowerAnim::WALK;
	}
}

void ALCCharacter::Crouch(bool _IsCrouch)
{
	Super::Crouch(_IsCrouch);

	bIsCrouch = true;

	if (CurLowerAnimType != ECharLowerAnim::CROUCH_IDLE)
	{
		UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::CROUCH_IDLE"), *FString(__FUNCSIG__));

		CurLowerAnimType = ECharLowerAnim::CROUCH_IDLE;
	}
	else if (CurLowerAnimType != ECharLowerAnim::CROUCH_WALK)
	{
		UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::CROUCH_WALK"), *FString(__FUNCSIG__));

		CurLowerAnimType = ECharLowerAnim::CROUCH_WALK;
	}
}

void ALCCharacter::UnCrouch(bool _IsCrouch)
{
	Super::UnCrouch(_IsCrouch);

	bIsCrouch = false;

	if (CurLowerAnimType == ECharLowerAnim::CROUCH_IDLE)
	{
		UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::IDLE"), *FString(__FUNCSIG__));

		CurLowerAnimType = ECharLowerAnim::IDLE;
	}
	else if (CurLowerAnimType == ECharLowerAnim::CROUCH_WALK)
	{
		UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::WALK"), *FString(__FUNCSIG__));

		CurLowerAnimType = ECharLowerAnim::WALK;
	}
}

void ALCCharacter::Sprint()
{
	bIsSprint = !bIsSprint;

	if (true == bIsSprint)
	{
		UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::SPRINT"), *FString(__FUNCSIG__));

		CurLowerAnimType = ECharLowerAnim::SPRINT;
	}
	else
	{
		if (true == bIsMoving)
		{
			UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::WALK"), *FString(__FUNCSIG__));

			CurLowerAnimType = ECharLowerAnim::WALK;
		}
		else
		{
			return;
		}
	}
}

#pragma endregion 




