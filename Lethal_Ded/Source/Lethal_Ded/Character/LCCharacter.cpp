// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LCCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"
// 함선 테스트
#include "Level/Stuff/Ship/Ship.h"
#include "kismet/GameplayStatics.h"
// 함선 테스트
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

// 함선 테스트
void ALCCharacter::ControlDoorsOpen()
{
	AShip* Ship = Cast<AShip>(UGameplayStatics::GetActorOfClass(GetWorld(), AShip::StaticClass()));

	if (nullptr == Ship)
	{
#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Warning, TEXT("[%s] : Ship is null"), *FString(__FUNCSIG__));
		}
#endif
		return;
	}

	Ship->ControlDoorsOpen();
}

void ALCCharacter::ControlDoorsClose()
{
	AShip* Ship = Cast<AShip>(UGameplayStatics::GetActorOfClass(GetWorld(), AShip::StaticClass()));

	if (nullptr == Ship)
	{
#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Warning, TEXT("[%s] : Ship is null"), *FString(__FUNCSIG__));
		}
#endif
		return;
	}

	Ship->ControlDoorsClose();
}

void ALCCharacter::ControlTheLever()
{
	AShip* Ship = Cast<AShip>(UGameplayStatics::GetActorOfClass(GetWorld(), AShip::StaticClass()));

	if (nullptr == Ship)
	{
#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Warning, TEXT("[%s] : Ship is null"), *FString(__FUNCSIG__));
		}
#endif
		return;
	}

	Ship->ControlTheLever();
}

void ALCCharacter::ControlSDoorLeft()
{
	AShip* Ship = Cast<AShip>(UGameplayStatics::GetActorOfClass(GetWorld(), AShip::StaticClass()));

	if (nullptr == Ship)
	{
#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Warning, TEXT("[%s] : Ship is null"), *FString(__FUNCSIG__));
		}
#endif
		return;
	}

	Ship->ControlSDoorLeft();
}

void ALCCharacter::ControlSDoorRight()
{
	AShip* Ship = Cast<AShip>(UGameplayStatics::GetActorOfClass(GetWorld(), AShip::StaticClass()));

	if (nullptr == Ship)
	{
#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Warning, TEXT("[%s] : Ship is null"), *FString(__FUNCSIG__));
		}
#endif
		return;
	}

	Ship->ControlSDoorRight();
}
// 함선 테스트

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
	DOREPLIFETIME(ALCCharacter, bIsAttack);
	DOREPLIFETIME(ALCCharacter, bCanAttack);
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
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ALCCharacter::SprintStart_Server);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ALCCharacter::SprintEnd_Server);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ALCCharacter::AttackReady_Server);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &ALCCharacter::Attack_Server);
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
	SetMoveStatus_Server(false);

	const FVector2D MovementValue = _Axis2D.Get<FVector2D>();

	if (nullptr != Controller && true == MovementValue.IsNearlyZero(0.0f))
	{
		if (false == bIsCrouch)
		{
#if !UE_BUILD_SHIPPING
			if (true == bCanShowCharLog)
			{
				UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::IDLE"), *FString(__FUNCSIG__));
			}
#endif

			CurUpperAnimType = ECharUpperAnim::IDLE;	// Replicated Test
			CurLowerAnimType = ECharLowerAnim::IDLE;
		}
		else
		{
#if !UE_BUILD_SHIPPING
			if (true == bCanShowCharLog)
			{
				UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::CROUCH_IDLE"), *FString(__FUNCSIG__));
			}
#endif

			CurLowerAnimType = ECharLowerAnim::CROUCH_IDLE;
		}
	}
}

void ALCCharacter::Move(const FInputActionValue& _Axis2D)
{
	SetMoveStatus_Server(true);

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
			if (false == bIsCrouch)
			{
#if !UE_BUILD_SHIPPING
				if (true == bCanShowCharLog)
				{
					UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::WALK"), *FString(__FUNCSIG__));
				}
#endif

				CurUpperAnimType = ECharUpperAnim::TWOHANDS;	// Replicated Tests
				CurLowerAnimType = ECharLowerAnim::WALK;
			}
			else
			{
#if !UE_BUILD_SHIPPING
				if (true == bCanShowCharLog)
				{
					UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::CROUCH_WALK"), *FString(__FUNCSIG__));
				}
#endif

				CurLowerAnimType = ECharLowerAnim::CROUCH_WALK;
			}
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

	if (GetVelocity().ZAxisVector.IsNearlyZero(2.0f))
	{
#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::JUMP"), *FString(__FUNCSIG__));
		}
#endif

		CurLowerAnimType = ECharLowerAnim::JUMP;
	}

	FTimerHandle myTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			if (false == bIsMoving)
			{
#if !UE_BUILD_SHIPPING
				if (true == bCanShowCharLog)
				{
					UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::IDLE"), *FString(__FUNCSIG__));
				}
#endif

				CurLowerAnimType = ECharLowerAnim::IDLE;
			}
			else
			{
#if !UE_BUILD_SHIPPING
				if (true == bCanShowCharLog)
				{
					UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::WALK"), *FString(__FUNCSIG__));
				}
#endif

				CurLowerAnimType = ECharLowerAnim::WALK;
			}

			// 타이머 초기화
			GetWorld()->GetTimerManager().ClearTimer(myTimerHandle);
		}), 0.1f, false);
}

void ALCCharacter::Crouch(bool _IsCrouch)
{
	Super::Crouch();

	if (false == bIsMoving)
	{
#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::CROUCH_IDLE"), *FString(__FUNCSIG__));
		}
#endif

		CurLowerAnimType = ECharLowerAnim::CROUCH_IDLE;
	}
	else
	{
#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::CROUCH_WALK"), *FString(__FUNCSIG__));
		}
#endif

		CurLowerAnimType = ECharLowerAnim::CROUCH_WALK;
	}
}

void ALCCharacter::UnCrouch(bool _IsCrouch)
{
	Super::UnCrouch();

	if (false == bIsMoving)
	{
#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::IDLE"), *FString(__FUNCSIG__));
		}
#endif

		CurLowerAnimType = ECharLowerAnim::IDLE;
	}
	else
	{
#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::WALK"), *FString(__FUNCSIG__));
		}
#endif

		CurLowerAnimType = ECharLowerAnim::WALK;
	}
}

void ALCCharacter::SprintStart_Server_Implementation()
{
	SprintStart();
}

void ALCCharacter::SprintStart_Implementation()
{
	// 임시
	if (true == bIsCrouch)
	{
		return;
	}

	if (true == bIsMoving)
	{
		bIsSprint = true;

		GetCharacterMovement()->MaxWalkSpeed = 600.0f;

#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::SPRINT"), *FString(__FUNCSIG__));
		}
#endif

		CurLowerAnimType = ECharLowerAnim::SPRINT;
	}
	else
	{
		bIsSprint = false;

#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::IDLE"), *FString(__FUNCSIG__));
		}
#endif

		CurLowerAnimType = ECharLowerAnim::IDLE;
	}
}

void ALCCharacter::SprintEnd_Server_Implementation()
{
	SprintEnd();
}

void ALCCharacter::SprintEnd_Implementation()
{
	// 임시
	if (true == bIsCrouch)
	{
		return;
	}

	bIsSprint = false;

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	if (true == bIsMoving)
	{
#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::WALK"), *FString(__FUNCSIG__));
		}
#endif

		CurLowerAnimType = ECharLowerAnim::WALK;
	}
	else
	{
#if !UE_BUILD_SHIPPING
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurLowerAnimType = ECharLowerAnim::IDLE"), *FString(__FUNCSIG__));
		}
#endif

		CurLowerAnimType = ECharLowerAnim::IDLE;
	}
}

void ALCCharacter::AttackReady_Server_Implementation()
{
	AttackReady();
}

void ALCCharacter::AttackReady_Implementation()
{
#if !UE_BUILD_SHIPPING
	if (true == bCanShowCharLog)
	{
		UE_LOG(LethalCompany_LOG, Warning, TEXT("[%s] : AttackReady"), *FString(__FUNCSIG__));
	}
#endif

	bIsAttack = true;
	bCanAttack = false;

#if !UE_BUILD_SHIPPING
	if (true == bCanShowCharLog)
	{
		UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurUpperAnimType = ECharUpperAnim::ATTACKREADY"), *FString(__FUNCSIG__));
	}
#endif

	CurUpperAnimType = ECharUpperAnim::ATTACKREADY;
}

void ALCCharacter::Attack_Server_Implementation()
{
	Attack();
}

void ALCCharacter::Attack_Implementation()
{
#if !UE_BUILD_SHIPPING
	if (true == bCanShowCharLog)
	{
		UE_LOG(LethalCompany_LOG, Warning, TEXT("[%s] : Attack"), *FString(__FUNCSIG__));
	}
#endif

	bCanAttack = true;

#if !UE_BUILD_SHIPPING
	if (true == bCanShowCharLog)
	{
		UE_LOG(LethalCompany_LOG, Log, TEXT("[%s] : CurUpperAnimType = ECharUpperAnim::ATTACK"), *FString(__FUNCSIG__));
	}
#endif

	CurUpperAnimType = ECharUpperAnim::ATTACK;

	FTimerHandle myTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			CurUpperAnimType = ECharUpperAnim::SHOVEL;

			bIsAttack = false;
			bCanAttack = false;

			// 타이머 초기화
			GetWorld()->GetTimerManager().ClearTimer(myTimerHandle);
		}), 0.26f, false);
}

#pragma endregion 




