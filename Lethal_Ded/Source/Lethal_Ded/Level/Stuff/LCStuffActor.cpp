// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Stuff/LCStuffActor.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ALCStuffActor::ALCStuffActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);

}

// Called when the game starts or when spawned
void ALCStuffActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALCStuffActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALCStuffActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALCStuffActor, StaticMeshComponent);
}

