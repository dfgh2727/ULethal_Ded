// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Rooms/MasterRoom.h"
#include "Components/BoxComponent.h"

// Sets default values
AMasterRoom::AMasterRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = DefaultSceneRoot;

	Exit = CreateDefaultSubobject<USceneComponent>("Exit");
	Exit->SetupAttachment(DefaultSceneRoot);

	Geometry = CreateDefaultSubobject<USceneComponent>("Geometry");
	Geometry->SetupAttachment(DefaultSceneRoot);

	Collision = CreateDefaultSubobject<USceneComponent>("Collision");
	Collision->SetupAttachment(DefaultSceneRoot);
	
	SpawnPointFolder = CreateDefaultSubobject<USceneComponent>("SpawnPointFolder");
	SpawnPointFolder->SetupAttachment(DefaultSceneRoot);

	OverlapFolder = CreateDefaultSubobject<USceneComponent>("OverlapFolder");
	OverlapFolder->SetupAttachment(DefaultSceneRoot);

	OverlapBox = CreateDefaultSubobject<UBoxComponent>("OverlapBox");
	OverlapBox->SetupAttachment(OverlapFolder);

}

// Called when the game starts or when spawned
void AMasterRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

