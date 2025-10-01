// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Rooms/Door.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/LCCharacter.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bNetLoadOnClient = true;


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
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ADoor::OverlapEnd);

	if (DoorOpenCurve != nullptr)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("OpenDoorAnimation"));

		DoorOpenTimeline.AddInterpFloat(DoorOpenCurve, TimelineProgress);
		DoorOpenTimeline.SetLooping(false);

		FOnTimelineFloat TimelineProgress2;
		TimelineProgress2.BindUFunction(this, FName("CloseDoorAnimation"));

		DoorCloseTimeline.AddInterpFloat(DoorCloseCurve, TimelineProgress2);
		DoorCloseTimeline.SetLooping(false);
	}

}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	DoorOpenTimeline.TickTimeline(DeltaTime);
	DoorCloseTimeline.TickTimeline(DeltaTime);
	
}


void ADoor::ServerSetDoorState_Implementation(bool _bOpen)
{
	if (!bDoorOverlap) return; // 겹치지 않으면 열지 않음

	bOpen = _bOpen;

	// 서버에서도 Timeline 실행
	if (bOpen)
		DoorOpenTimeline.PlayFromStart();
	else
		DoorCloseTimeline.PlayFromStart();
}

void ADoor::OnRep_Open()
{
	if (!bDoorOverlap) return;

	if (bOpen)
		DoorOpenTimeline.PlayFromStart();
	else
		DoorCloseTimeline.PlayFromStart();

}
void ADoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADoor, bDoorOverlap);
	DOREPLIFETIME(ADoor, bOpen);
}

void ADoor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bDoorOverlap = true;

}

void ADoor::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bDoorOverlap = false;

}

void ADoor::OpenDoorAnimation(float Value)
{
	FRotator StartRotation = { 0.0f, 0.0f, 0.0f };
	FRotator TargetRotation = { 0.0f, 90.0f, 0.0f };

	FRotator CurRot = FMath::Lerp(StartRotation, TargetRotation, Value);
	Door->SetRelativeRotation(CurRot);
}

void ADoor::CloseDoorAnimation(float Value)
{
	FRotator StartRotation = { 0.0f, 0.0f, 0.0f };
	FRotator TargetRotation = { 0.0f, -90.0f, 0.0f };

	FRotator CurRot = FMath::Lerp(StartRotation, TargetRotation, Value);
	Door->SetRelativeRotation(CurRot);
}
