// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Rooms/RoomGenerator.h"
#include "Level/Rooms/MasterRoom.h"
#include "Level/Rooms/RoomDataTable.h"

#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"

#include "Engine/World.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARoomGenerator::ARoomGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bNetLoadOnClient = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = DefaultSceneRoot;


}

// Called when the game starts or when spawned
void ARoomGenerator::BeginPlay()
{
	Super::BeginPlay();

	// 서버에서만 실행
	if (HasAuthority())
	{
		SpawnStartRoom();

		if (RoomDataTable)
		{
			TArray<FName> RowNames = RoomDataTable->GetRowNames();
			for (const FName& Name : RowNames)
			{
				FRoomDataRow* Row = RoomDataTable->FindRow<FRoomDataRow>(Name, TEXT(""));
				if (Row && Row->RoomList)
				{
					RoomList.Add(Row->RoomList);
				}
			}
		}

		SpawnNextRoom();
	}
}

// Called every frame
void ARoomGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoomGenerator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARoomGenerator, LastestRoom);
}

void ARoomGenerator::SpawnStartRoom_Implementation()
{
	FTransform Transform = DefaultSceneRoot->GetComponentTransform();

	if (nullptr != StartRoom)
	{
		AMasterRoom* SpawnedRoom = GetWorld()->SpawnActor<AMasterRoom>(StartRoom, Transform);
		
		TArray<USceneComponent*> Exits;
		SpawnedRoom->GetExit()->GetChildrenComponents(true, Exits);

		ExitsList.Append(Exits);
	}
}

void ARoomGenerator::SpawnNextRoom_Implementation()
{
	int ExitRandomIndex = FMath::RandRange(0, ExitsList.Num() - 1);
	SelectExit = ExitsList[ExitRandomIndex];
	
	if (IsValid(SelectExit))
	{
		TSubclassOf<AMasterRoom> SelectedRoom = nullptr;

		if (!RoomList.IsEmpty())
		{
			int RoomRandomIndex = static_cast<int>(FMath::RandRange(0, RoomList.Num() - 1));
			SelectedRoom = RoomList[RoomRandomIndex];
		}

		FVector RoomLocation = SelectExit->GetComponentLocation();
		FRotator RoomRotation = SelectExit->GetComponentRotation();

		if (nullptr != SelectedRoom)
		{
			AMasterRoom* SpawnedRoom = GetWorld()->SpawnActor<AMasterRoom>(SelectedRoom, RoomLocation, RoomRotation);

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARoomGenerator::CheckOverlap, 0.2f, false);

			LastestRoom = SpawnedRoom;

			RoomAmount -= 1;


		}
	}

}

void ARoomGenerator::AddOverLapRoomToList()
{
	if (!LastestRoom) return;

	UBoxComponent* OverlapBox = LastestRoom->GetOverlapBox();
	if (!OverlapBox) return;

	TArray<UPrimitiveComponent*> OverlappingComponents;
	OverlapBox->GetOverlappingComponents(OverlappingComponents);

	for (UPrimitiveComponent* Comp : OverlappingComponents)
	{
		if (UBoxComponent* BoxComp = Cast<UBoxComponent>(Comp))
		{
			OverlapList.Add(BoxComp);
		}
	}

}

void ARoomGenerator::CheckOverlap()
{
	AddOverLapRoomToList();

	if (!OverlapList.IsEmpty())
	{
		GetWorld()->DestroyActor(LastestRoom);
	}
	else
	{
		if (ExitsList.Contains(SelectExit))
		{
			ExitsList.Remove(SelectExit);
		}
		
		TArray<USceneComponent*> Exits;
		LastestRoom->GetExit()->GetChildrenComponents(true, Exits);

		ExitsList.Append(Exits);

	}

	OverlapList.Empty();

	if (RoomAmount > 0)
	{
		SpawnNextRoom();
	}
	else
	{
		CloseHoles();
	}
}

void ARoomGenerator::CloseHoles()
{
	for (int i = 0; i < ExitsList.Num(); i++)
	{
		FTransform Transform = ExitsList[i]->GetComponentTransform();
		GetWorld()->SpawnActor<AActor>(Wall, Transform);
	}
}