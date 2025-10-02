// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_Attack.h"
#include "Character/LCCharacter.h"


void UAnimNotifyState_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ALCCharacter* PlayerCharacter = Cast<ALCCharacter>(MeshComp->GetOwner());
	if (nullptr != PlayerCharacter)
	{
		PlayerCharacter->SetCanAttack(false);
		PlayerCharacter->SetIsAttack(true);
		PlayerCharacter->SetCurUpperAnimType(ECharUpperAnim::ATTACK);
	}
}

void UAnimNotifyState_Attack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UAnimNotifyState_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ALCCharacter* PlayerCharacter = Cast<ALCCharacter>(MeshComp->GetOwner());
	if (nullptr != PlayerCharacter)
	{
		PlayerCharacter->SetCanAttack(true);
		PlayerCharacter->SetIsAttack(false);
		PlayerCharacter->SetCurUpperAnimType(ECharUpperAnim::SHOVEL);
	}
}