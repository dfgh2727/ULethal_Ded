// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Global/LCEnum.h"
#include "LCCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API ULCCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void NativeBeginPlay() override;

	void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void ChangeAnimation(ECharAnim _CurAnimType, FName _UpperSectionName = TEXT("None"), FName _LowerSectionName = TEXT("None"));

private:
	ECharAnim CurAnimType = ECharAnim::IDLE;

	FName UpperSectionName = TEXT("");
	FName LowerSectionName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* UpperMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* LowerMontage;

	UAnimMontage* CurUpperMontage;
	UAnimMontage* CurLowerMontage;
};
