// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/Items/Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API AWeapon : public AItem
{
	GENERATED_BODY()
public:
	AWeapon();

	virtual void Tick(float DeltaTime) override;

	bool IsHit() const
	{
		return bHit;
	}

	void EnableHitBox();
	void DisableHitBox();

protected:
	virtual void BeginPlay() override;


private:
	UFUNCTION()
	void OverlapHitBoxBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OverlapHitBoxEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Weapon", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* HitBox;

	bool bHit = false;

};
