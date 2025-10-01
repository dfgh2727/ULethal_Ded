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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Door")
	void OpenDoor()
	{
		bOpen = true;
	}

	UFUNCTION(BlueprintCallable, Category = "Door")
	void CloseDoor()
	{
		bOpen = false;
	}


	UFUNCTION()
	void OnRep_Open();

	UFUNCTION(Server, Reliable)
	void ServerSetDoorState(bool _bOpen);
	void ServerSetDoorState_Implementation(bool _bOpen);
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

	UPROPERTY()
	FTimeline DoorCloseTimeline;

	UPROPERTY(EditAnywhere, Category = "Level|Door", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* DoorOpenCurve;

	UPROPERTY(EditAnywhere, Category = "Level|Door", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* DoorCloseCurve;

	UFUNCTION()
	void OpenDoorAnimation(float Value);

	UFUNCTION()
	void CloseDoorAnimation(float Value);

	UPROPERTY(ReplicatedUsing = OnRep_Open)
	bool bOpen;


	UPROPERTY(Replicated)
	bool bDoorOverlap = false;
};
