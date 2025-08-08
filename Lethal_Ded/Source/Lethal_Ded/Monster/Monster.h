// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterDataTable.h"
//#include "Monster/MonsterAnimInstance.h"
#include "Monster.generated.h"


UCLASS()
class LETHAL_DED_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

	void SetDataKey(const FString& _ItemDataKey)
	{
		DataKey = _ItemDataKey;
	}


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	
	void NetSyncMonster();
	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Reliable, Server)
	void ChangeAnimation(int _CurAnimnation, FName _SectionName = TEXT("None"));
	void ChangeAnimation_Implementation(int _CurAnimnation, FName _SectionName = TEXT("None"));

	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
	void ChangeAnimation_Multicast(int _CurAnimnation, FName _SectionName = TEXT("None"));
	void ChangeAnimation_Multicast_Implementation(int _CurAnimnation, FName _SectionName = TEXT("None"));


	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "Data")
	FString DataKey = "";

private:
	const FMonsterDataRow* Data = nullptr;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Data")
	class UAIDataObject* AIData = nullptr;


	UPROPERTY(VisibleAnywhere, Category = "Data")
	class UDataTable* DataTables = nullptr;
	class UDataTable* MonsterDataTable = nullptr;


};
