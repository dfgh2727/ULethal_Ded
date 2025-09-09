// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/Stuff/LCStuffActor.h"
#include "Ship.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API AShip : public ALCStuffActor
{
	GENERATED_BODY()

public:
	AShip();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void ControlDoors(bool bOpen);
	void ControlTheLever();

private:
	void OpenDoors(float DeltaTime);
	void CloseDoors(float DeltaTime);

	void MoveTheLever(float DeltaTime);

	//void PullTheLever(float DeltaTime);
	//void PushTheLever(float DeltaTime);


	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "LeftDoor", meta = (AllowprivateAccess = "true"))
	UStaticMeshComponent* LeftDoorComponent = nullptr;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "RightDoor", meta = (AllowprivateAccess = "true"))
	UStaticMeshComponent* RightDoorComponent = nullptr;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Lever", meta = (AllowprivateAccess = "true"))
	UStaticMeshComponent* LeverComponent = nullptr;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "StorageBody", meta = (AllowprivateAccess = "true"))
	UStaticMeshComponent* StorageBodyComponent = nullptr;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "LSDoor", meta = (AllowprivateAccess = "true"))
	UStaticMeshComponent* LSDoorComponent = nullptr;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "RSDoor", meta = (AllowprivateAccess = "true"))
	UStaticMeshComponent* RSDoorComponent = nullptr;

	float DoorMovement = 300.0f;
	//bool bDoorMove = true;
	bool bDoItOnce = false;
	bool bSign = false;

	bool bLeverMove = false;
	bool bLeverIsDown = false;
};
