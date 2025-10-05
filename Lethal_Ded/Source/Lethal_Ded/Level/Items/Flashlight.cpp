// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Items/Flashlight.h"
#include "Components/SpotLightComponent.h"

AFlashlight::AFlashlight()
{
	SpotlightComponent = CreateDefaultSubobject<USpotLightComponent>("SpotlightComponent");
	SpotlightComponent->SetupAttachment(StaticMeshComponent);
	SpotlightComponent->SetRelativeLocation({ 0.0f, 0.0f, 17.0f });
	SpotlightComponent->SetRelativeRotation({ 90.0f, 0.0f, 0.0f });
	SpotlightComponent->SetVisibility(false);

}

void AFlashlight::BeginPlay()
{
	AItem::BeginPlay();

	curBatteryLevel = totalBatteryLevel;
}

void AFlashlight::Tick(float DeltaTime)
{
	AItem::Tick(DeltaTime);

	if (bFlash == true)
	{
		float DrainRate = 1.0f;
		curBatteryLevel = FMath::Max(0.f, curBatteryLevel - DrainRate * DeltaTime);
	}

	if (curBatteryLevel <= 0)
	{
		bFlash = false;
	}
	else
	{
		bFlash = true;
	}

	if (bFlash == true && bBatteryRemained == true)
	{
		SpotlightComponent->SetVisibility(true);
	}
	else
	{
		SpotlightComponent->SetVisibility(false);

	}
}
