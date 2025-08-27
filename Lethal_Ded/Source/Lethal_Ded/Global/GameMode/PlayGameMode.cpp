// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GameMode/PlayGameMode.h"
#include "Character/LCCharacter.h"
#include "Global/Controller/LCPlayerController.h"
#include "Global/Component/TimeEventComponent.h"


APlayGameMode::APlayGameMode()
{
	TimeEventComponent = CreateDefaultSubobject<UTimeEventComponent>("TimeEventComponent");

	bUseSeamlessTravel = true;
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void APlayGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayGameMode::PostLogin(APlayerController* PlayerController)
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

void APlayGameMode::SpawnAndPossess(ALCPlayerController* Controller)
{
	FVector Location = FVector(0.0, 0.0, 300.0);
	FRotator Rotation = FRotator::ZeroRotator;


	ALCPlayerController* LCPlayerController = Controller;
	if (LCPlayerController != nullptr)
	{
		LCPlayerController->GetPawn()->Destroy();
	}

	AActor* NewActor = GetWorld()->SpawnActor<AActor>(Character);
	ALCCharacter* NewCharacter = Cast<ALCCharacter>(NewActor);
	LCPlayerController->Possess(NewCharacter);

	FString MyString = TEXT("YOUR CLIENT IS CONNECTED");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MyString);
}