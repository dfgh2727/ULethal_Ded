// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GameMode/PlayGameMode.h"
#include "Character/LCCharacter.h"
#include "Global/Controller/LCPlayerController.h"
#include "Global/Component/TimeEventComponent.h"
#include "Level/Stuff/Ship/Ship.h"

#include "GameFramework/PlayerStart.h"



APlayGameMode::APlayGameMode()
{
	TimeEventComponent = CreateDefaultSubobject<UTimeEventComponent>("TimeEventComponent");

	bUseSeamlessTravel = true;
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnShip();

	TimeEventComponent->AddEndEvent(1.0f, [this]()
		{
			bShipIsLanding = true;
		});
}

void APlayGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShipIsLanding == true && ShipPtr != nullptr)
	{
		ShipPtr->ShipLand(DeltaTime);
		//if (배가 만약 착륙 위치에 있다면)
		//{
		//		bShipIsLanding =false;
		//}
	}
	
}

void APlayGameMode::SpawnShip()
{
	if (SpawnTarget_Ship != nullptr)
	{
		ShipPtr = GetWorld()->SpawnActor<AShip>(SpawnTarget_Ship);
		ShipPtr->SetActorLocation(ShipSpawnPos);
	}
}


AShip* APlayGameMode::GetShipPtr()
{
	return ShipPtr;
}


