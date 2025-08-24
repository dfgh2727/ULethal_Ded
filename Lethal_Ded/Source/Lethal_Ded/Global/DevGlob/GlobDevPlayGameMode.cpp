// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/DevGlob/GlobDevPlayGameMode.h"
#include "Global/DevGlob/GlobDevPlayerController.h"
#include "Global/DevGlob/GlobDevCharacter.h"

AGlobDevPlayGameMode::AGlobDevPlayGameMode()
{
}

void AGlobDevPlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	bBeginPlay = true;
}

void AGlobDevPlayGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGlobDevPlayGameMode::PostLogin(APlayerController* PlayerController)
{
	Super::PostLogin(PlayerController);

	bPostLogin = true;

	/*AGlobDevPlayerController* GlobDevPlayerController = Cast<AGlobDevPlayerController>(PlayerController);
	if (GlobDevPlayerController != nullptr)
	{
		SpawnAndPossess(GlobDevPlayerController);
	}*/
}

void AGlobDevPlayGameMode::SpawnAndPossess(AGlobDevPlayerController* Controller)
{
	FVector Location = FVector(0.0, 0.0, 300.0);
	FRotator Rotation = FRotator::ZeroRotator;

	if (HasAuthority())
	{
		AGlobDevPlayerController* GlobDevPlayerController = Controller;
		if (GlobDevPlayerController != nullptr)
		{
			//Location = GlobDevPlayerController->GetPawn()->GetActorLocation();
			GlobDevPlayerController->GetPawn()->Destroy();
		}

		AActor* NewActor = GetWorld()->SpawnActor<AActor>(GlobDevCharacter);
		AGlobDevCharacter* NewCharacter = Cast<AGlobDevCharacter>(NewActor);
		GlobDevPlayerController->Possess(NewCharacter);
		
	}
	
}

bool AGlobDevPlayGameMode::CheckPossibilitySAP()
{
	if (bPostLogin == true && bBeginPlay == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
