// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_Damage.h"
#include <Object/Interface/AttackInterface.h>

void UAnimNotifyState_Damage::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	IAttackInterface* Interface = Cast<IAttackInterface>(MeshComp->GetOwner());

	if (Interface == nullptr) return;

	Interface->AttackStart();

}
void UAnimNotifyState_Damage::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);


}
void UAnimNotifyState_Damage::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	IAttackInterface* Interface = Cast<IAttackInterface>(MeshComp->GetOwner());

	if (Interface == nullptr) return;

	Interface->AttackEnd();
}