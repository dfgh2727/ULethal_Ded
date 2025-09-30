// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/Stuff/LCStuffActor.h"
#include "Ship.generated.h"

class UWidgetComponent;
class UShipTerminalUserWidget;

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

	void ControlDoorsOpen();
	void ControlDoorsClose();
	void ControlTheLever();

	void ControlSDoorLeft();
	void ControlSDoorRight();

private:
	void OpenDoors(float DeltaTime);
	void CloseDoors(float DeltaTime);

	void MoveTheLever(float DeltaTime);

	void MoveLSDoor(float DeltaTime);
	void MoveRSDoor(float DeltaTime);

	void OrderTravelToRend(APlayerController* PlayerController);
	void OrderTravelToCompany(APlayerController* PlayerController);
	void OrderTravelToReady(APlayerController* PlayerController);


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


	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Terminal", meta = (AllowprivateAccess = "true"))
	UWidgetComponent* TerminalComponent = nullptr;


	UShipTerminalUserWidget* ShipTerminalUserWidget = nullptr;

	float DoorMovement = 300.0f;

	UPROPERTY(Replicated)
	bool bDoItOnce = false;
	UPROPERTY(Replicated)
	bool bSign = false;
	UPROPERTY(Replicated)
	bool bDoorsOpen = false;

	UPROPERTY(Replicated)
	bool bLeverMove = false;
	UPROPERTY(Replicated)
	bool bLeverIsDown = false;

	UPROPERTY(Replicated)
	bool bLSDoorMove = false;
	UPROPERTY(Replicated)
	bool bRSDoorMove = false;

	UPROPERTY(Replicated)
	bool bLSDoorShut = true;
	UPROPERTY(Replicated)
	bool bRSDoorShut = true;
};
