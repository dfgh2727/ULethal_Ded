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

void ULCCharacterAnimInstance::ChangeAnimation(ECharAnim _CurAnimType, FName _UpperSectionName/* = TEXT("None")*/, FName _LowerSectionName/* = TEXT("None")*/)
{
	if (nullptr == UpperMontage)
	{
		UE_LOG(LethalCompany_LOG, Error, TEXT("[%s] : UpperMontage is null"), *FString(__FUNCSIG__));
		return;
	}
	if (nullptr == LowerMontage)
	{
		UE_LOG(LethalCompany_LOG, Error, TEXT("[%s] : LowerMontage is null"), *FString(__FUNCSIG__));
		return;
	}

	Montage_Play(UpperMontage, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f, true);
	Montage_JumpToSection(_UpperSectionName);

	Montage_Play(LowerMontage, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f, false);
	Montage_JumpToSection(_LowerSectionName);

	CurAnimType = _CurAnimType;

	CurUpperMontage = UpperMontage;
	UpperSectionName = _UpperSectionName;

	CurLowerMontage = LowerMontage;
	LowerSectionName = _LowerSectionName;
}
