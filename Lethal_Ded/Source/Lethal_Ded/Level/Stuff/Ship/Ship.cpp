// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Stuff/Ship/Ship.h"
#include "Net/UnrealNetwork.h"


AShip::AShip()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	{
		LeftDoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoorComponent"));
		LeftDoorComponent->SetupAttachment(RootComponent);

		RightDoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoorComponent"));
		RightDoorComponent->SetupAttachment(RootComponent);

		LeverComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverComponent"));
		LeverComponent->SetupAttachment(RootComponent);

		StorageBodyComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StorageBodyComponent"));
		StorageBodyComponent->SetupAttachment(RootComponent);

		LSDoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LSDoorComponent"));
		LSDoorComponent->SetupAttachment(RootComponent);

		RSDoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RSDoorComponent"));
		RSDoorComponent->SetupAttachment(RootComponent);

	}

	
}

void AShip::BeginPlay()
{
	Super::BeginPlay();
}

void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDoItOnce == true && bSign == true)
	{
		OpenDoors(DeltaTime);
	}
	else if (bDoItOnce == true && bSign == false)
	{
		CloseDoors(DeltaTime);
	}

	if (bLeverMove == true)
	{
		MoveTheLever(DeltaTime);
	}

}

void AShip::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShip, LeftDoorComponent);
	DOREPLIFETIME(AShip, RightDoorComponent);
}

void AShip::OpenDoors(float DeltaTime)
{
	/*if(bDoorMove == true)
	{
		FVector CurLeftLocation = LeftDoorComponent->GetRelativeLocation();
		CurLeftLocation.X -= DeltaTime * DoorMovement;
		LeftDoorComponent->SetRelativeLocation(CurLeftLocation);
	
		FVector CurRighttLocation = RightDoorComponent->GetRelativeLocation();
		CurRighttLocation.X += DeltaTime * DoorMovement;
		RightDoorComponent->SetRelativeLocation(CurRighttLocation);
	}*/

	FVector CurLeftLocation = LeftDoorComponent->GetRelativeLocation();
	CurLeftLocation.X -= DeltaTime * DoorMovement;
	LeftDoorComponent->SetRelativeLocation(CurLeftLocation);

	FVector CurRighttLocation = RightDoorComponent->GetRelativeLocation();
	CurRighttLocation.X += DeltaTime * DoorMovement;
	RightDoorComponent->SetRelativeLocation(CurRighttLocation);

	FVector Locate = LeftDoorComponent->GetRelativeLocation();

	if (Locate.X < -600.0f)
	{
		//bDoorMove = false;
		bDoItOnce = false;
		LeftDoorComponent->SetVisibility(false);
		RightDoorComponent->SetVisibility(false);
	}
}

void AShip::CloseDoors(float DeltaTime)
{
	LeftDoorComponent->SetVisibility(true);
	RightDoorComponent->SetVisibility(true);

	/*if (bDoorMove == true)
	{
		FVector CurLeftLocation = LeftDoorComponent->GetRelativeLocation();
		CurLeftLocation.X += DeltaTime * DoorMovement;
		LeftDoorComponent->SetRelativeLocation(CurLeftLocation);

		FVector CurRighttLocation = RightDoorComponent->GetRelativeLocation();
		CurRighttLocation.X -= DeltaTime * DoorMovement;
		RightDoorComponent->SetRelativeLocation(CurRighttLocation);
	}*/

	FVector CurLeftLocation = LeftDoorComponent->GetRelativeLocation();
	CurLeftLocation.X += DeltaTime * DoorMovement;
	LeftDoorComponent->SetRelativeLocation(CurLeftLocation);

	FVector CurRighttLocation = RightDoorComponent->GetRelativeLocation();
	CurRighttLocation.X -= DeltaTime * DoorMovement;
	RightDoorComponent->SetRelativeLocation(CurRighttLocation);

	FVector Locate = LeftDoorComponent->GetRelativeLocation();

	if (Locate.X > 0.0f)
	{
		//bDoorMove = false;
		bDoItOnce = false;
	}
}

void AShip::MoveTheLever(float DeltaTime)
{
	if (bLeverIsDown == false)
	{
		FRotator CurRotation = LeverComponent->GetRelativeRotation();
		CurRotation.Roll -= DeltaTime * 100;
		LeverComponent->SetRelativeRotation(CurRotation);

		if (CurRotation.Roll <= -46)
		{
			bLeverMove = false;
			bLeverIsDown = true;
		}
	}
	else
	{
		FRotator CurRotation = LeverComponent->GetRelativeRotation();
		CurRotation.Roll += DeltaTime * 100;
		LeverComponent->SetRelativeRotation(CurRotation);
		
		if (CurRotation.Roll >= 1)
		{
			bLeverMove = false;
			bLeverIsDown = false;
		}
	}
	
}

//void AShip::PushTheLever(float DeltaTime)
//{
//	FRotator CurRotation = LeverComponent->GetRelativeRotation();
//	CurRotation.Roll += DeltaTime * 100;
//	LeverComponent->SetRelativeRotation(CurRotation);
//
//	if (CurRotation.Roll >= 1)
//	{
//		bLeverMove = false;
//	}
//}

void AShip::ControlDoors(bool bOpen) //문의 개폐조절 함수. true는 열기, false는 닫기
{
	bSign = bOpen;
	bDoItOnce = true;
	//bDoorMove = true;
}

void AShip::ControlTheLever()
{
	bLeverMove = true;
}

void AShip::ControlSDoorLeft()
{

}

void AShip::ControlSDoorRight()
{

}

