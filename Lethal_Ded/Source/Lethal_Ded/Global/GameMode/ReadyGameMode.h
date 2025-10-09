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

protected:
	void SpawnShip();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Spawning", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ALCCharacter> Character;

	class UTimeEventComponent* TimeEventComponent = nullptr;

	class AShip* ShipPtr = nullptr;
	
};
