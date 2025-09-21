// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Rooms/Door.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;


	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = DefaultSceneRoot;

	Frame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	Frame->SetupAttachment(DefaultSceneRoot);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(DefaultSceneRoot);

	Trigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
	Trigger->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OverlapBegin);

	if (DoorOpenCurve != nullptr)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("OpenDoor"));

		DoorOpenTimeline.AddInterpFloat(DoorOpenCurve, TimelineProgress);
		DoorOpenTimeline.SetLooping(false);
	}

}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorOpenTimeline.TickTimeline(DeltaTime);
}

void ADoor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bDoorOverlap = true;
	if (bOpen == false)
	{
		DoorOpenTimeline.PlayFromStart();
		bOpen = true;
	}
}

void ADoor::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bDoorOverlap = false;

}

void ADoor::OpenDoor(float Value)
{
	FRotator StartRotation = { 0.0f, 0.0f, 0.0f };
	FRotator TargetRotation = { 0.0f, 90.0f, 0.0f };

	FRotator CurRot = FMath::Lerp(StartRotation, TargetRotation, Value);
	Door->SetRelativeRotation(CurRot);
}
