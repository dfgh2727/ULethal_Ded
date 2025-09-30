// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/LCEnum.h"
#include "Item.generated.h"

UCLASS()
class LETHAL_DED_API AItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level|Item")
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level|Item")
	UDataTable* ItemDataTable;

	bool CanGrab()
	{
		return bGrabbable;
	}

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level|Item", meta = (AllowPrivateAccess = "true"))
	//EItemType GripType = EItemType::ONEHAND;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level|Item", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DefaultSceneRoot;


	UPROPERTY(VisibleAnywhere, Category = "Level|Item", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level|Item", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* GrabTrigger;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WidgetClass;


	void SetItemInfo();
	void SetWidgetRotation();
	void SetGrabble();


	FString ItemName = "NONE";

	EItemType ItemGripType = EItemType::ONEHAND;
	
	int ItemPrice = 0;

	bool bWidgetVisible = false;
	bool bGrabbable = false;

	const int ITEMSHOWDISTANCE = 500.0f;
};
