// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/GameMode/LCGameMode.h"
#include "PlayGameMode.generated.h"

/**
 * 
 */



UCLASS()
class LETHAL_DED_API APlayGameMode : public ALCGameMode
{
	GENERATED_BODY()
	
public:
	APlayGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;



private:

	void SpawnShip();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Spawning_Ship", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AShip>SpawnTarget_Ship;

	class AShip* ShipPtr = nullptr;

	FVector ShipSpawnPos = FVector(0.0f, 0.0f, 1500.0f);

	class UTimeEventComponent* TimeEventComponent = nullptr;

	bool bShipIsLanding = false;
	bool bShipIsTakingOff = false;
};
