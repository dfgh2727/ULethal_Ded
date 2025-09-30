// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterDataTable.h"
#include "Object/Interface/AttackInterface.h"
#include "Net/UnrealNetwork.h" 
//#include "Monster/MonsterAnimInstance.h"
#include "Monster.generated.h"


UCLASS()
class LETHAL_DED_API AMonster : public ACharacter, public IAttackInterface
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






	// 공격 시
	void AttackStart();
	void AttackEnd();
	void HandleDeath(AActor* Killer);
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION(Server, Reliable)
	void C2S_AttachCharacter(AActor* Target);
	void C2S_AttachCharacter_Implementation(AActor* Target);

	UFUNCTION(NetMulticast, Reliable)
	void S2C_ApplyCaptured(AActor* Target, bool bCaptured);
	void S2C_ApplyCaptured_Implementation(AActor* Target, bool bCaptured);

	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Reliable, Server)
	void ChangeAnimation(int _CurAnimnation, FName _SectionName = TEXT("None"));
	void ChangeAnimation_Implementation(int _CurAnimnation, FName _SectionName = TEXT("None"));

	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
	void ChangeAnimation_Multicast(int _CurAnimnation, FName _SectionName = TEXT("None"));
	void ChangeAnimation_Multicast_Implementation(int _CurAnimnation, FName _SectionName = TEXT("None"));

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "Data")
	EAIState AIStateValue = EAIState::MAX;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "Data")
	FString DataKey = "";

private:
	const FMonsterDataRow* Data = nullptr;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Data")
	class UAIDataObject* AIData = nullptr;


	UPROPERTY(VisibleAnywhere, Category = "Data")
	class UDataTable* DataTables = nullptr;
	class UDataTable* MonsterDataTable = nullptr;

public:
	UPROPERTY(Replicated)
	bool bIsWaitTime = false;

	// (설정) 몇 번의 공격을 맞으면 사망할지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play")
	int32 AttacksToKill = 3;

	// (상태) 현재 누적 공격 횟수
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Play")
	int32 CurrentAttackCount = 0;

	// (상태) 사망 여부
	UPROPERTY(ReplicatedUsing = OnRep_IsDead, VisibleAnywhere, BlueprintReadOnly, Category = "Play")
	bool bIsDead = false;

	UFUNCTION()
	void OnRep_IsDead();

	// 사망 브로드캐스트
	UFUNCTION(NetMulticast, Reliable)
	void S2C_OnKilled(AActor* Killer);
	void S2C_OnKilled_Implementation(AActor* Killer);
};
