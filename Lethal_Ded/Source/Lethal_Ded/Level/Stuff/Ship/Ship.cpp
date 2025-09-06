// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Stuff/Ship/Ship.h"
#include "Net/UnrealNetwork.h"


AShip::AShip()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	LeftDoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoorComponent"));
	LeftDoorComponent->SetupAttachment(RootComponent);

	RightDoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoorComponent"));
	RightDoorComponent->SetupAttachment(RootComponent);
}

void AShip::BeginPlay()
{
	Super::BeginPlay();
}

void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OpenDoors(DeltaTime);
}

void AShip::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShip, LeftDoorComponent);
	DOREPLIFETIME(AShip, RightDoorComponent);
}

void AShip::OpenDoors(float DeltaTime)
{
	{
		FVector CurLeftLocation = LeftDoorComponent->GetRelativeLocation();
		CurLeftLocation.X -= DeltaTime * 100;
		LeftDoorComponent->SetRelativeLocation(CurLeftLocation);
	}
	{
		FVector CurRighttLocation = LeftDoorComponent->GetRelativeLocation();
		CurRighttLocation.X += DeltaTime * 100;
		RightDoorComponent->SetRelativeLocation(CurRighttLocation);
	}
}

void AShip::CloseDoors()
{

}

