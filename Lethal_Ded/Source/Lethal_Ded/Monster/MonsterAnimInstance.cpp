// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAnimInstance.h"
#include <Net/UnrealNetwork.h>

void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	SkeletalMeshComponent = GetOwningComponent();
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DetlaSeconds)
{
	Super::NativeUpdateAnimation(DetlaSeconds);
}



void UMonsterAnimInstance::ChangeAnimation(int _CurAnimationType, FName _SectionName)
{
	if (false == AnimMontages.Contains(_CurAnimationType))
	{
		return;
	}

	UAnimMontage* Montage = AnimMontages[_CurAnimationType];

	if (CurMontage == Montage)
	{
		if (SectionName != _SectionName)
		{
			Montage_JumpToSection(_SectionName);
		} 
	}

	ChangeAnimationEvent(Montage, SectionName);

	CurMontage = Montage;
	CurAnimationType = _CurAnimationType;
	SectionName = _SectionName;

}
