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

	if (bDoItOnce == true)
	{
		if (bSign == true && bDoorsOpen == false)
		{
			OpenDoors(DeltaTime);
		}
		else if (bSign == false && bDoorsOpen == true)
		{
			CloseDoors(DeltaTime);
		}
	}
	

	if (bLeverMove == true)
	{
		MoveTheLever(DeltaTime);
	}

	if (bLSDoorMove == true)
	{
		MoveLSDoor(DeltaTime);
	}

	if (bRSDoorMove == true)
	{
		MoveRSDoor(DeltaTime);
	}

}

void AShip::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShip, LeftDoorComponent);
	DOREPLIFETIME(AShip, RightDoorComponent);
	DOREPLIFETIME(AShip, LeverComponent);
	DOREPLIFETIME(AShip, StorageBodyComponent);
	DOREPLIFETIME(AShip, LSDoorComponent);
	DOREPLIFETIME(AShip, RSDoorComponent);

	DOREPLIFETIME(AShip, bDoItOnce);
	DOREPLIFETIME(AShip, bSign);
	DOREPLIFETIME(AShip, bDoorsOpen);

	DOREPLIFETIME(AShip, bLeverMove);
	DOREPLIFETIME(AShip, bLeverIsDown);

	DOREPLIFETIME(AShip, bLSDoorMove);
	DOREPLIFETIME(AShip, bRSDoorMove);
	DOREPLIFETIME(AShip, bLSDoorShut);
	DOREPLIFETIME(AShip, bRSDoorShut);

}

void AShip::OpenDoors(float DeltaTime)
{
	FVector CurLeftLocation = LeftDoorComponent->GetRelativeLocation();
	CurLeftLocation.X -= DeltaTime * DoorMovement;
	LeftDoorComponent->SetRelativeLocation(CurLeftLocation);

	FVector CurRighttLocation = RightDoorComponent->GetRelativeLocation();
	CurRighttLocation.X += DeltaTime * DoorMovement;
	RightDoorComponent->SetRelativeLocation(CurRighttLocation);

	if (CurLeftLocation.X < -600.0f)
	{
		bDoItOnce = false;
		bDoorsOpen = true;
		LeftDoorComponent->SetVisibility(false);
		RightDoorComponent->SetVisibility(false);
	}
}

void AShip::CloseDoors(float DeltaTime)
{
	LeftDoorComponent->SetVisibility(true);
	RightDoorComponent->SetVisibility(true);

	FVector CurLeftLocation = LeftDoorComponent->GetRelativeLocation();
	CurLeftLocation.X += DeltaTime * DoorMovement;
	LeftDoorComponent->SetRelativeLocation(CurLeftLocation);

	FVector CurRighttLocation = RightDoorComponent->GetRelativeLocation();
	CurRighttLocation.X -= DeltaTime * DoorMovement;
	RightDoorComponent->SetRelativeLocation(CurRighttLocation);

	if (CurLeftLocation.X > 0.0f)
	{
		bDoItOnce = false;
		bDoorsOpen = false;
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

void AShip::MoveLSDoor(float DeltaTime)
{
	if (bLSDoorShut == true)
	{
		FRotator CurRotation = LSDoorComponent->GetRelativeRotation();
		CurRotation.Yaw += DeltaTime * 100;
		LSDoorComponent->SetRelativeRotation(CurRotation);

		if (CurRotation.Yaw >= 160)
		{
			bLSDoorMove = false;
			bLSDoorShut = false;
		}
	}
	else
	{
		FRotator CurRotation = LSDoorComponent->GetRelativeRotation();
		CurRotation.Yaw -= DeltaTime * 100;
		LSDoorComponent->SetRelativeRotation(CurRotation);

		if (CurRotation.Yaw <= 0)
		{
			bLSDoorMove = false;
			bLSDoorShut = true;
		}
	}
}

void AShip::MoveRSDoor(float DeltaTime)
{
	if (bRSDoorShut == true)
	{
		FRotator CurRotation = RSDoorComponent->GetRelativeRotation();
		CurRotation.Yaw -= DeltaTime * 100;
		RSDoorComponent->SetRelativeRotation(CurRotation);

		if (CurRotation.Yaw <= -160)
		{
			bRSDoorMove = false;
			bRSDoorShut = false;
		}
	}
	else
	{
		FRotator CurRotation = RSDoorComponent->GetRelativeRotation();
		CurRotation.Yaw += DeltaTime * 100;
		RSDoorComponent->SetRelativeRotation(CurRotation);

		if (CurRotation.Yaw >= 0)
		{
			bRSDoorMove = false;
			bRSDoorShut = true;
		}
	}
}


void AShip::ControlDoorsOpen() //입구 컨트롤 함수, 열기
{
	bSign = true;
	bDoItOnce = true;
}

void AShip::ControlDoorsClose() //입구 컨트롤 함수, 닫기
{
	bSign = false;
	bDoItOnce = true;
}

void AShip::ControlTheLever() //레버 컨트롤 함수
{
	bLeverMove = true;
}

void AShip::ControlSDoorLeft() //저장고(Storage) 왼쪽문 컨트롤 함수
{
	bLSDoorMove = true;
}

void AShip::ControlSDoorRight() //저장고(Storage) 오른쪽문 컨트롤 함수
{
	bRSDoorMove = true;
}

