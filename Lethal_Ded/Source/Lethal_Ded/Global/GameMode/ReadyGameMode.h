// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/GameMode/LCGameMode.h"
#include "ReadyGameMode.generated.h"


class ALCCharacter;
/**
 * 
 */
UCLASS()
class LETHAL_DED_API AReadyGameMode : public ALCGameMode
{
	GENERATED_BODY()

	AReadyGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void PostLogin(APlayerController* PlayerController) override;
	void SpawnAndPossess(class ALCPlayerController* Controller);

	void OrderShipServerTravelToPlay(const FString& TargetLevel);
	void OrderShipServerTravelToCompany(const FString& TargetLevel);


protected:
	void SpawnShip();
	void CheckShipIsSpawned();

	UFUNCTION(Server, Reliable)
	void ShipServerTravelToPlay(const FString& TargetLevel);
	void ShipServerTravelToPlay_Implementation(const FString& TargetLevel);

	UFUNCTION(Server, Reliable)
	void ShipServerTravelToCompany(const FString& TargetLevel);
	void ShipServerTravelToCompany_Implementation(const FString& TargetLevel);

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Spawning", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ALCCharacter> Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Spawning_Ship", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AShip>SpawnTarget_Ship;
	
	class UTimeEventComponent* TimeEventComponent = nullptr;

	class AShip* ShipPtr = nullptr;
	
	class ULCGameInstance* LCGameInstance = nullptr;

	FVector PlayerSpawnPos = FVector(-300.0f, 1500.0f, 1800.0f);
	FVector ShipSpawnPos = FVector(0.0f, 0.0f, 1500.0f);

};
