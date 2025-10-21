// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LCCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Level/Items/Item.h"
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
	GetMesh()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

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

	bCanAttack = true;
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

	TraceForInteractable();
}

void ALCCharacter::LCCharLog(const FString _Func, const FString _TEXT)
{
#if !UE_BUILD_SHIPPING
	if (true == bCanShowCharLog)
	{
		UE_LOG(LethalCompany_LOG, Warning, TEXT("[%s]"), *_Func);
		UE_LOG(LethalCompany_LOG, Log, TEXT("%s"), *_TEXT);
	}
#endif
}

// 함선 테스트
void ALCCharacter::ControlDoorsOpen()
{
	AShip* Ship = Cast<AShip>(UGameplayStatics::GetActorOfClass(GetWorld(), AShip::StaticClass()));

	if (nullptr == Ship)
	{
		LCCharLog(TEXT("ALCCharacter::ControlDoorsOpen"), TEXT("Ship is null"));
		return;
	}

	Ship->ControlDoorsOpen();
}

void ALCCharacter::ControlDoorsClose()
{
	AShip* Ship = Cast<AShip>(UGameplayStatics::GetActorOfClass(GetWorld(), AShip::StaticClass()));

	if (nullptr == Ship)
	{
		LCCharLog(TEXT("ALCCharacter::ControlDoorsClose"), TEXT("Ship is null"));
		return;
	}

	Ship->ControlDoorsClose();
}

void ALCCharacter::ControlTheLever()
{
	AShip* Ship = Cast<AShip>(UGameplayStatics::GetActorOfClass(GetWorld(), AShip::StaticClass()));

	//추가된 코드
	APlayerController* CurController = Cast<APlayerController>(GetController());
	Ship->SetPlayerControllerPtr(CurController);

	if (nullptr == Ship)
	{
		LCCharLog(TEXT("ALCCharacter::ControlTheLever"), TEXT("Ship is null"));
		return;
	}

	Ship->ControlTheLever();
}

void ALCCharacter::ControlSDoorLeft()
{
	AShip* Ship = Cast<AShip>(UGameplayStatics::GetActorOfClass(GetWorld(), AShip::StaticClass()));

	if (nullptr == Ship)
	{
		LCCharLog(TEXT("ALCCharacter::ControlSDoorLeft"), TEXT("Ship is null"));
		return;
	}

	Ship->ControlSDoorLeft();
}

void ALCCharacter::ControlSDoorRight()
{
	AShip* Ship = Cast<AShip>(UGameplayStatics::GetActorOfClass(GetWorld(), AShip::StaticClass()));

	if (nullptr == Ship)
	{
		LCCharLog(TEXT("ALCCharacter::ControlSDoorRight"), TEXT("Ship is null"));
		return;
	}

	Ship->ControlSDoorRight();
}
// 함선 테스트

// 라인 트레이스
void ALCCharacter::TraceForInteractable()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC)
	{
		return;
	}

	FVector CameraPos;
	FRotator CameraRot;
	PC->GetPlayerViewPoint(CameraPos, CameraRot);

	FVector Start = CameraPos;
	FVector End = Start + (CameraRot.Vector() * TraceDistance);

	FHitResult HitResult;
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(TraceForInteractable), true, this);
	TraceParams.bReturnPhysicalMaterial = false;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		TraceParams
	);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		UPrimitiveComponent* HitComp = HitResult.GetComponent();

		bool bHasTag = false;

		if (HitComp)
		{
			TArray<USceneComponent*> ComponentsToCheck;
			ComponentsToCheck.Add(HitComp);

			USceneComponent* ParentComp = HitComp->GetAttachParent();
			while (ParentComp)
			{
				TArray<USceneComponent*> ParentChildren;
				ParentComp->GetChildrenComponents(true, ParentChildren);
				for (USceneComponent* Child : ParentChildren)
				{
					if (Child)
					{
						ComponentsToCheck.AddUnique(Child);
					}
				}
				ParentComp = ParentComp->GetAttachParent();
			}

			TArray<USceneComponent*> MyChildren;
			HitComp->GetChildrenComponents(true, MyChildren);
			for (USceneComponent* Child : MyChildren)
			{
				if (Child)
				{
					ComponentsToCheck.AddUnique(Child);
				}
			}

			// 태그 디버깅
			for (USceneComponent* Comp : ComponentsToCheck)
			{
				if (!Comp)
				{
					continue;
				}

				for (const FName& Tag : Comp->ComponentTags)
				{
					if (true == bCanShowCharLog)
					{
						UE_LOG(LethalCompany_LOG, Log, TEXT("Tag Check - Comp: %s | Tag: %s"), *Comp->GetName(), *Tag.ToString());
					}

					if (Tag != "None")
					{
						TargetTagName = Tag;
					}

					if (Comp->ComponentHasTag(TargetTagName))
					{
						bHasTag = true;
						HitComp = Cast<UPrimitiveComponent>(Comp);
						break;
					}
				}

				if (bHasTag)
				{
					break;
				}
			}

			//// 맞는 컴포넌트 태그 가졌음?
			//if (HitComp->ComponentHasTag(TargetTagName))
			//{
			//	bHasTag = true;
			//}
			//else
			//{
			//	// 없을 경우, 부모 컴포넌트 확인
			//	USceneComponent* ParentComp = HitComp->GetAttachParent();
			//	while (ParentComp && !bHasTag)
			//	{
			//		if (ParentComp->ComponentHasTag(TargetTagName))
			//		{
			//			HitComp = Cast<UPrimitiveComponent>(ParentComp);
			//			bHasTag = true;
			//			break;
			//		}
			//		ParentComp = ParentComp->GetAttachParent();
			//	}

			//	// 모든 자식 컴포넌트도 확인
			//	if (!bHasTag)
			//	{
			//		USceneComponent* RootForSearch = HitComp->GetAttachParent();
			//		if (RootForSearch == nullptr)
			//		{
			//			RootForSearch = HitComp;
			//		}

			//		TArray<USceneComponent*> AllChildren;
			//		RootForSearch->GetChildrenComponents(true, AllChildren);

			//		for (USceneComponent* ChildComp : AllChildren)
			//		{
			//			if (ChildComp && ChildComp->ComponentHasTag(TargetTagName))
			//			{
			//				HitComp = Cast<UPrimitiveComponent>(ChildComp);
			//				bHasTag = true;
			//				break;
			//			}
			//		}
			//	}
			//}
		}

		if (bHasTag)
		{
			FocusedActor = HitActor;
			FocusedComponent = HitComp;

			if (true == bCanShowCharLog)
			{
				DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0, 0, 1.f);
				UE_LOG(LethalCompany_LOG, Log, TEXT("Interactable Found: %s (Tag: %s)"), *HitComp->GetName(), *TargetTagName.ToString());
			}
		}
		else
		{
			FocusedActor = nullptr;
			FocusedComponent = nullptr;

			if (true == bCanShowCharLog)
			{
				DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, 0, 0, 1.f);
			}

		}
	}
	else
	{
		FocusedActor = nullptr;
		FocusedComponent = nullptr;

		if (true == bCanShowCharLog)
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0, 0, 1.f);
		}
	}
}

void ALCCharacter::OnInteract_Server_Implementation()
{
	OnInteract();
}

void ALCCharacter::OnInteract_Implementation()
{
	if (FocusedComponent)
	{
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Warning, TEXT("Interacted with component: %s (Actor: %s)"),
				*FocusedComponent->GetName(),
				*FocusedActor->GetName());
		}

		if (FocusedComponent->ComponentHasTag("Shovel"))
		{
			if (true == bCanShowCharLog)
			{
				UE_LOG(LethalCompany_LOG, Log, TEXT("This component is Shovel!"));
			}

			FocusedActor;

			Equip(FocusedActor);

			CurUpperAnimType = ECharUpperAnim::SHOVEL;
		}
	}
}
// 라인 트레이스

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
	DOREPLIFETIME(ALCCharacter, DeathCount);
	DOREPLIFETIME(ALCCharacter, AttackCount);
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

	//if (false == bIsAttack && false == bCanAttack)
	//{
	//	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ALCCharacter::AttackReady_Server);
	//	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &ALCCharacter::Attack_Server);
	//}

	if (true == bCanAttack)
	{
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ALCCharacter::Attack_Server);
	}

	EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this, &ALCCharacter::OnInteract_Server);
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
			LCCharLog(TEXT("ALCCharacter::Idle"), TEXT("CurLowerAnimType = ECharLowerAnim::IDLE"));

			//CurUpperAnimType = ECharUpperAnim::IDLE;	// Replicated Test
			CurLowerAnimType = ECharLowerAnim::IDLE;
		}
		else
		{
			LCCharLog(TEXT("ALCCharacter::Idle"), TEXT("CurLowerAnimType = ECharLowerAnim::CROUCH_IDLE"));

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
				LCCharLog(TEXT("ALCCharacter::Move"), TEXT("CurLowerAnimType = ECharLowerAnim::WALK"));

				//CurUpperAnimType = ECharUpperAnim::TWOHANDS;	// Replicated Tests
				CurLowerAnimType = ECharLowerAnim::WALK;
			}
			else
			{
				LCCharLog(TEXT("ALCCharacter::Move"), TEXT("CurLowerAnimType = ECharLowerAnim::CROUCH_WALK"));

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
		LCCharLog(TEXT("ALCCharacter::Jump"), TEXT("CurLowerAnimType = ECharLowerAnim::JUMP"));

		CurLowerAnimType = ECharLowerAnim::JUMP;
	}

	FTimerHandle myTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			if (false == bIsMoving)
			{
				LCCharLog(TEXT("ALCCharacter::Jump"), TEXT("CurLowerAnimType = ECharLowerAnim::IDLE"));

				CurLowerAnimType = ECharLowerAnim::IDLE;
			}
			else
			{
				LCCharLog(TEXT("ALCCharacter::Jump"), TEXT("CurLowerAnimType = ECharLowerAnim::WALK"));

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
		LCCharLog(TEXT("ALCCharacter::Crouch"), TEXT("CurLowerAnimType = ECharLowerAnim::CROUCH_IDLE"));

		CurLowerAnimType = ECharLowerAnim::CROUCH_IDLE;
	}
	else
	{
		LCCharLog(TEXT("ALCCharacter::Crouch"), TEXT("CurLowerAnimType = ECharLowerAnim::CROUCH_WALK"));

		CurLowerAnimType = ECharLowerAnim::CROUCH_WALK;
	}
}

void ALCCharacter::UnCrouch(bool _IsCrouch)
{
	Super::UnCrouch();

	if (false == bIsMoving)
	{
		LCCharLog(TEXT("ALCCharacter::UnCrouch"), TEXT("CurLowerAnimType = ECharLowerAnim::IDLE"));

		CurLowerAnimType = ECharLowerAnim::IDLE;
	}
	else
	{
		LCCharLog(TEXT("ALCCharacter::UnCrouch"), TEXT("CurLowerAnimType = ECharLowerAnim::WALK"));

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

		LCCharLog(TEXT("ALCCharacter::SprintStart_Implementation"), TEXT("CurLowerAnimType = ECharLowerAnim::SPRINT"));

		CurLowerAnimType = ECharLowerAnim::SPRINT;
	}
	else
	{
		bIsSprint = false;

		LCCharLog(TEXT("ALCCharacter::SprintStart_Implementation"), TEXT("CurLowerAnimType = ECharLowerAnim::IDLE"));

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
		LCCharLog(TEXT("ALCCharacter::SprintEnd_Implementation"), TEXT("CurLowerAnimType = ECharLowerAnim::WALK"));

		CurLowerAnimType = ECharLowerAnim::WALK;
	}
	else
	{
		LCCharLog(TEXT("ALCCharacter::SprintEnd_Implementation"), TEXT("CurLowerAnimType = ECharLowerAnim::IDLE"));

		CurLowerAnimType = ECharLowerAnim::IDLE;
	}
}

void ALCCharacter::AttackReady_Server_Implementation()
{
	AttackReady();
}

void ALCCharacter::AttackReady_Implementation()
{
	int a = 0;
}

void ALCCharacter::Attack_Server_Implementation()
{
	Attack();
}

void ALCCharacter::Attack_Implementation()
{
	if (false == bCanAttack)
	{
		return;
	}

	if (false == bIsAttack && CurUpperAnimType == ECharUpperAnim::SHOVEL)
	{
		LCCharLog(TEXT("ALCCharacter::Attack_Implementation"), TEXT("Attack"));

		bIsAttack = true;

		LCCharLog(TEXT("ALCCharacter::Attack_Implementation"), TEXT("CurUpperAnimType = ECharUpperAnim::ATTACK"));

		CurUpperAnimType = ECharUpperAnim::ATTACK;
	}
}

void ALCCharacter::Equip(AActor* _Item)
{
	EquipItem = Cast<AItem>(_Item);

	if (EquipItem == nullptr)
	{
		if (true == bCanShowCharLog)
		{
			UE_LOG(LethalCompany_LOG, Log, TEXT("FocusedActor Tag: %s"), *FocusedActor->Tags[0].ToString());
		}

		LCCharLog(TEXT("ALCCharacter::Equip"), TEXT("EquipItem is null"));
		
		return;
	}

	EquipItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("ItemSocket"));
	EquipItem->SetActorRelativeLocation(FVector(0, 0, 0));
}

//void ALCCharacter::Hit(AActor* _Actor)
//{
//	if (true == _Actor->ActorHasTag(TEXT("Monster")))
//	{
//		APawn* DamagePawn = Cast<APawn>(_Actor);
//		AController* Con = nullptr;
//		if (nullptr == DamagePawn)
//		{
//			Con = DamagePawn->GetController();
//		}
//
//		DamagePawn->GetController();
//		UGameplayStatics::ApplyDamage(this, AttackCount, Con, _Actor, nullptr);
//	}
//}

#pragma endregion 




