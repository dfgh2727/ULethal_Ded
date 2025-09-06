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

	//OpenDoors(DeltaTime);
	//CloseDoors(DeltaTime);
}

void AShip::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShip, LeftDoorComponent);
	DOREPLIFETIME(AShip, RightDoorComponent);
}

void AShip::OpenDoors(float DeltaTime)
{
	if(bDoorMove == true)
	{
		FVector CurLeftLocation = LeftDoorComponent->GetRelativeLocation();
		CurLeftLocation.X -= DeltaTime * DoorMovement;
		LeftDoorComponent->SetRelativeLocation(CurLeftLocation);
	
		FVector CurRighttLocation = RightDoorComponent->GetRelativeLocation();
		CurRighttLocation.X += DeltaTime * DoorMovement;
		RightDoorComponent->SetRelativeLocation(CurRighttLocation);
	}

	FVector Locate = LeftDoorComponent->GetRelativeLocation();

	if (Locate.X < -600.0f)
	{
		bDoorMove = false;
		LeftDoorComponent->SetVisibility(false);
		RightDoorComponent->SetVisibility(false);
	}
}

void AShip::CloseDoors(float DeltaTime)
{
	LeftDoorComponent->SetVisibility(true);
	RightDoorComponent->SetVisibility(true);

	if (bDoorMove == true)
	{
		FVector CurLeftLocation = LeftDoorComponent->GetRelativeLocation();
		CurLeftLocation.X += DeltaTime * DoorMovement;
		LeftDoorComponent->SetRelativeLocation(CurLeftLocation);

		FVector CurRighttLocation = RightDoorComponent->GetRelativeLocation();
		CurRighttLocation.X -= DeltaTime * DoorMovement;
		RightDoorComponent->SetRelativeLocation(CurRighttLocation);
	}

	FVector Locate = LeftDoorComponent->GetRelativeLocation();

	if (Locate.X > 0.0f)
	{
		bDoorMove = false;
	}
}

