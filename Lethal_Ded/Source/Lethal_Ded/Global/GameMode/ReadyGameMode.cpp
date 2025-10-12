// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GameMode/ReadyGameMode.h"
#include "Character/LCCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Global/Controller/LCPlayerController.h"
#include "Global/Component/TimeEventComponent.h"
#include "Level/Stuff/Ship/Ship.h"

AReadyGameMode::AReadyGameMode()
{
	TimeEventComponent = CreateDefaultSubobject<UTimeEventComponent>("TimeEventComponent");

	bUseSeamlessTravel = true;
}

void AReadyGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnShip();
}

void AReadyGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AReadyGameMode::PostLogin(APlayerController* PlayerController)
{
	Super::PostLogin(PlayerController);

	TimeEventComponent->AddEndEvent(0.5f, [this, PlayerController]()
		{
			ALCPlayerController* LCPlayerController = Cast<ALCPlayerController>(PlayerController);
			if (LCPlayerController != nullptr)
			{
				SpawnAndPossess(LCPlayerController);
			}
		});
}

void AReadyGameMode::SpawnAndPossess(ALCPlayerController* Controller)
{
	FVector Location = FVector(0.0, 0.0, 300.0);
	FRotator Rotation = FRotator::ZeroRotator;


	ALCPlayerController* LCPlayerController = Controller;
	if (LCPlayerController != nullptr)
	{
		LCPlayerController->GetPawn()->Destroy();
	}

	AActor* NewActor = GetWorld()->SpawnActor<AActor>(Character);
	NewActor->SetActorLocation(PlayerSpawnPos);

	ALCCharacter* NewCharacter = Cast<ALCCharacter>(NewActor);
	LCPlayerController->Possess(NewCharacter);

	FString MyString = TEXT("YOUR CLIENT IS CONNECTED");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MyString);
}

void AReadyGameMode::SpawnShip()
{
	if (SpawnTarget_Ship != nullptr)
	{
		ShipPtr = GetWorld()->SpawnActor<AShip>(SpawnTarget_Ship);
		ShipPtr->SetActorLocation(ShipSpawnPos);
	}
}

void AReadyGameMode::CheckShipIsSpawned()
{

}

void AReadyGameMode::OrderShipServerTravelToPlay(const FString& TargetLevel)
{
	ShipServerTravelToPlay_Implementation(TargetLevel);
}

void AReadyGameMode::OrderShipServerTravelToCompany(const FString& TargetLevel)
{
	ShipServerTravelToCompany_Implementation(TargetLevel);
}


void AReadyGameMode::ShipServerTravelToPlay_Implementation(const FString& TargetLevel)
{
	if (ShipPtr != nullptr)
	{
		
	}
}

void AReadyGameMode::ShipServerTravelToCompany_Implementation(const FString& TargetLevel)
{
}
