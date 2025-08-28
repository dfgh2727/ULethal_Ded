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
	void ChangeAnimation(ECharUpperAnim _CurUpperAnimType, ECharLowerAnim _CurLowerAnimType);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	ECharUpperAnim CurUpperAnimType = ECharUpperAnim::MAX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	ECharLowerAnim CurLowerAnimType = ECharLowerAnim::MAX;
};
