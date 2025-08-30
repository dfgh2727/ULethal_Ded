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
	UDataTable* RoomDataTable;

	UPROPERTY(Replicated, BlueprintReadOnly)
	class AMasterRoom* LastestRoom;

	UFUNCTION(Server, Reliable)
	void SpawnNextRoom();

	UFUNCTION(Server, Reliable)
	void SpawnStartRoom();

private:

	void CheckOverlap();
	void AddOverLapRoomToList();
	void CloseHoles();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generator", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DefaultSceneRoot;
	class USceneComponent* SelectExit;

	TArray<class USceneComponent*> ExitsList;
	TArray<class UPrimitiveComponent*> OverlapList;
	TArray<TSubclassOf<AMasterRoom>> RoomList;

	int RoomAmount = 15;


};
