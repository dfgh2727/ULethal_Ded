// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LCCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Character/LCCharacterAnimInstance.h"
#include "Net/UnrealNetwork.h"


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
	
	CharAnimInst = Cast<ULCCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	CurUpperSectionName = TEXT("Idle_Upper");
	CurLowerSectionName = TEXT("Idle_Lower");
}

// Called every frame
void ALCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nullptr != CharAnimInst)
	{
		CharAnimInst->ChangeAnimation(CurAnimType, CurUpperSectionName, CurLowerSectionName);
	}
}

// Called to bind functionality to input
void ALCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALCCharacter::ChangeAnimation_Server_Implementation(ECharAnim _CurAnimType, FName _UpperSectionName/* = TEXT("None")*/, FName _LowerSectionName/* = TEXT("None")*/)
{
	ChangeAnimation(_CurAnimType, _UpperSectionName, _LowerSectionName);
}

void ALCCharacter::ChangeAnimation_Implementation(ECharAnim _CurAnimType, FName _UpperSectionName/* = TEXT("None")*/, FName _LowerSectionName/* = TEXT("None")*/)
{
	//CharAnimInst->ChangeAnimation(_CurAnimType, _UpperSectionName, _LowerSectionName);
	CurAnimType = _CurAnimType;
	CurUpperSectionName = _UpperSectionName;
	CurLowerSectionName = _LowerSectionName;
}

void ALCCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALCCharacter, CurAnimType);
	DOREPLIFETIME(ALCCharacter, CurUpperSectionName);
	DOREPLIFETIME(ALCCharacter, CurLowerSectionName);
}


