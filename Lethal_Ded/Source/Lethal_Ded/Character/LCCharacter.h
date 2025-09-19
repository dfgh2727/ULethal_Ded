// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/LCEnum.h"
#include "LCCharacter.generated.h"

UCLASS()
class LETHAL_DED_API ALCCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region LCCharacter_Base
public:
	// Sets default values for this character's properties
	ALCCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	float CurSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	float Stamina = 100.0f;

#pragma endregion 


#pragma region LCCharacter_Animation
public:
	UFUNCTION(BlueprintCallable, Reliable, Server)
	void ChangeAnimation_Server(ECharUpperAnim _CurUpperAnimType, ECharLowerAnim _CurLowerAnimType);
	void ChangeAnimation_Server_Implementation(ECharUpperAnim _CurUpperAnimType, ECharLowerAnim _CurLowerAnimType);

	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
	void ChangeAnimation(ECharUpperAnim _CurUpperAnimType, ECharLowerAnim _CurLowerAnimType);
	void ChangeAnimation_Implementation(ECharUpperAnim _CurUpperAnimType, ECharLowerAnim _CurLowerAnimType);

protected:

private:
	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	ECharUpperAnim CurUpperAnimType = ECharUpperAnim::MAX;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	ECharLowerAnim CurLowerAnimType = ECharLowerAnim::MAX;

#pragma endregion 


#pragma region LCCharacter_Sync
public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

protected:

private:

#pragma endregion 


#pragma region LCCharacter_Input
public:

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	class UInputAction* RotateAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	class UInputAction* CrouchAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction = nullptr;

#pragma endregion 


#pragma region LCCharacter_Action
public:
	UFUNCTION(BlueprintCallable)
	void Rotate(const struct FInputActionValue& _Axis2D);

	UFUNCTION(BlueprintCallable)
	void Move(const struct FInputActionValue& _Axis2D);

	UFUNCTION(BlueprintCallable)
	void Idle(const struct FInputActionValue& _Axis2D);

	void Jump() override;

	void Crouch(bool _IsCrouch) override;
	void UnCrouch(bool _IsCrouch) override;

	UFUNCTION(BlueprintCallable)
	void Sprint();

	UFUNCTION(BlueprintCallable, Reliable, Server)
	void SetMovementValue_Server(const FVector2D& _MovementValue);
	void SetMovementValue_Server_Implementation(const FVector2D& _MovementValue)
	{
		SetMovementValue(_MovementValue);
	}

	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
	void SetMovementValue(const FVector2D& _MovementValue);
	void SetMovementValue_Implementation(const FVector2D& _MovementValue)
	{
		CurMovementValue = _MovementValue;
	}

protected:

private:
	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	FVector2D CurMovementValue;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	bool bIsMoving = false;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	bool bIsFalling = false;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	bool bIsCrouch = false;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, category = "LCCharacter", meta = (AllowPrivateAccess = "true"))
	bool bIsSprint = false;

#pragma endregion 
};
