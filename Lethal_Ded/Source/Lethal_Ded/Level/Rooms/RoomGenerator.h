// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomGenerator.generated.h"

UCLASS()
class LETHAL_DED_API ARoomGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
	TSubclassOf<class AMasterRoom> StartRoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
	TSubclassOf<AActor> Wall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
	TSubclassOf<AActor> Door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
	UDataTable* RoomDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
	UDataTable* ItemDataTable;

	UPROPERTY(Replicated, BlueprintReadOnly)
	class AMasterRoom* LastestRoom;

	UFUNCTION(Server, Reliable)
	void SpawnNextRoom();

	UFUNCTION(Server, Reliable)
	void SpawnStartRoom();

private:

	void AddSpawnPointToList();
	void SpawnItem();
	void AddOverLapRoomToList();
	void CheckOverlap();
	void CloseHoles();
	void SpawnDoor();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generator", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DefaultSceneRoot;
	class USceneComponent* SelectExit;
	class USceneComponent* SelectSpawnPoint;

	TArray<class USceneComponent*> ExitsList;
	TArray<class USceneComponent*> DoorsList;
	TArray<class USceneComponent*> SpawnPointsList;
	TArray<class UPrimitiveComponent*> OverlapList;
	TArray<TSubclassOf<AMasterRoom>> RoomList;
	TArray<TSubclassOf<class AItem>> ItemList;

	FRandomStream RandomStream;

	int RoomAmount = 15;
	int ItemAmount = 5;


};
