// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/DevGlob/GlobDevPlayGameMode.h"
#include "Global/DevGlob/GlobDevPlayerController.h"
#include "Global/DevGlob/GlobDevCharacter.h"

#include "Global/Component/TimeEventComponent.h"

AGlobDevPlayGameMode::AGlobDevPlayGameMode()
{
	TimeEventComponent = CreateDefaultSubobject<UTimeEventComponent>("TimeEventComponent");
}

void AGlobDevPlayGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AGlobDevPlayGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGlobDevPlayGameMode::PostLogin(APlayerController* PlayerController)
{
	Super::PostLogin(PlayerController);

	//FString Message = FString::Printf(TEXT("클라이언트가 접속했습니다"));
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);

	FString MyString = TEXT("YOUR CLIENT CONNECTED");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MyString);

	//TimeEventComponent->AddEndEvent(0.5f, [this, PlayerController]()
	//	{
	//		AGlobDevPlayerController* GlobDevPlayerController = Cast<AGlobDevPlayerController>(PlayerController);
	//		if (GlobDevPlayerController != nullptr)
	//		{
	//			SpawnAndPossess(GlobDevPlayerController);
	//		}
	//	});
}

void AGlobDevPlayGameMode::SpawnAndPossess(AGlobDevPlayerController* Controller)
{
	FVector Location = FVector(0.0, 0.0, 300.0);
	FRotator Rotation = FRotator::ZeroRotator;


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

