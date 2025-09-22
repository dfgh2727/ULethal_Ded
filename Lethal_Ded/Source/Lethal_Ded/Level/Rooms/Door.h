// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class LETHAL_DED_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



private:
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); 
	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level|Door", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Level|Door", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Frame = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Level|Door", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Door = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Trigger;

	UPROPERTY()
	FTimeline DoorOpenTimeline;

	UPROPERTY(EditAnywhere, Category = "Level|Door", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* DoorOpenCurve;

	UFUNCTION()
	void OpenDoor(float Value);

	bool bOpen = false;
	bool bDoorOverlap = false;
};
