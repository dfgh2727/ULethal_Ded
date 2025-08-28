// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LCCharacterAnimInstance.h"
#include "Lethal_Ded/Lethal_Ded.h"

void ULCCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void ULCCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void ULCCharacterAnimInstance::ChangeAnimation(ECharUpperAnim _CurUpperAnimType, ECharLowerAnim _CurLowerAnimType)
{
	CurUpperAnimType = _CurUpperAnimType;
	CurLowerAnimType = _CurLowerAnimType;
}


