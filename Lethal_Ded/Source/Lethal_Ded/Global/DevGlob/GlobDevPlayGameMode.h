// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/DevGlob/GlobDevGameMode.h"
#include "GlobDevPlayGameMode.generated.h"

class AGlobDevCharacter;
/**
 * 
 */
UCLASS()
class LETHAL_DED_API AGlobDevPlayGameMode : public AGlobDevGameMode
{
	GENERATED_BODY()

public:
	AGlobDevPlayGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void PostLogin(APlayerController* PlayerController) override;

	
	void SpawnAndPossess(class AGlobDevPlayerController* Controller);
	bool CheckPossibilitySAP();
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Spawning", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGlobDevCharacter> GlobDevCharacter;

	bool bPostLogin = false;
	bool bBeginPlay = false;
};
