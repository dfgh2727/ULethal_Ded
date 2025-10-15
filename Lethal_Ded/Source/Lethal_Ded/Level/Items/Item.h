// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/LCEnum.h"
#include "Level/Items/ItemDataTable.h"
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
	//virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level|Item", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Level|Item", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level|Item", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* GrabTrigger;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level|Item")
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level|Item")
	UDataTable* ItemDataTable;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	bool CanGrab() const
	{
		return bGrabbable;
	}

	EItemType GetItemGripType() const
	{
		return ItemGripType;
	}

	EItemInteractType GetItemInteractType() const
	{
		return ItemInteractType;
	}

	const FItemDataRow* GetItemDataRow() const
	{
		return ItemDataRow;
	}

	const UBoxComponent* GetGrabTrigger() const
	{
		return GrabTrigger;
	}

private:
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level|Item", meta = (AllowPrivateAccess = "true"))
	//EItemType GripType = EItemType::ONEHAND;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
	void SetItemInfo();
	void SetWidgetRotation();

	FItemDataRow* ItemDataRow = nullptr;
	FString ItemName = "NONE";
	EItemType ItemGripType = EItemType::ONEHAND;
	EItemInteractType ItemInteractType = EItemInteractType::NONE;
	
	int ItemPrice = 0;

	bool bWidgetVisible = false;
	bool bGrabbable = false;

	const int ITEMSHOWDISTANCE = 500.0f;

};
