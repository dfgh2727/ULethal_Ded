// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/LCEnum.h"
#include "Character/LCCharacterAnimInstance.h"
#include "LCCharacter.generated.h"

UCLASS()
class LETHAL_DED_API ALCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALCCharacter();

	UFUNCTION(BlueprintCallable, Reliable, Server)
	void ChangeAnimation_Server(ECharAnim _CurAnimType, FName _UpperSectionName = TEXT("None"), FName _LowerSectionName = TEXT("None"));
	void ChangeAnimation_Server_Implementation(ECharAnim _CurAnimType, FName _UpperSectionName = TEXT("None"), FName _LowerSectionName = TEXT("None"));

	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
	void ChangeAnimation(ECharAnim _CurAnimType, FName _UpperSectionName = TEXT("None"), FName _LowerSectionName = TEXT("None"));
	void ChangeAnimation_Implementation(ECharAnim _CurAnimType, FName _UpperSectionName = TEXT("None"), FName _LowerSectionName = TEXT("None"));

	ULCCharacterAnimInstance* GetCharAnimInst()
	{
		return CharAnimInst;
	}

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	ECharAnim CurAnimType = ECharAnim::IDLE;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	FName CurUpperSectionName = TEXT("None");

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	FName CurLowerSectionName = TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	float CurSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	ULCCharacterAnimInstance* CharAnimInst = nullptr;
};
