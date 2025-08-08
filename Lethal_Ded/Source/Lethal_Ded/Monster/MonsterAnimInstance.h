// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void NativeBeginPlay() override;

	void NativeUpdateAnimation(float DetlaSeconds) override;

	//void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	template<typename EnumType>
	void ChangeAnimation(EnumType _Animation, FName _SectionName = TEXT("None"))
	{
		return ChangeAnimation(static_cast<int>(_Animation), _SectionName);
	}

	int GetCurAnimationType()
	{
		return CurAnimationType;
	}

	void ChangeAnimation(int _Animation, FName _SectionName = TEXT("None"));

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeAnimationEvent(UAnimMontage* _Montage, FName _SectionName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	TMap<int, UAnimMontage*> AnimMontages;

private:

	//UPROPERTY(Replicated, BlueprintReadWrite, Category = "Anim", meta = (AllowPrivateAccess = "true"))
	int CurAnimationType = 0;

	//UPROPERTY(Replicated, BlueprintReadWrite, Category = "Anim", meta = (AllowPrivateAccess = "true"))

	FName SectionName = TEXT("");

	//UPROPERTY(Replicated, BlueprintReadWrite, Category = "Anim", meta = (AllowPrivateAccess = "true"))

	UAnimMontage* CurMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComponent;
};
