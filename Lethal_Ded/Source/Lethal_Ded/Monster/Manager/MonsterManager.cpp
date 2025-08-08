// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Manager/MonsterManager.h"
#include "MonsterManager.h"

#include "Monster/Monster.h"
// Sets default values for this component's properties
UMonsterManager::UMonsterManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UMonsterManager::CreateMonster(const FString& _ItemName, FVector _OriginPos)
{

	FString Path = TEXT("/Game/Blueprints/Monster/BP_Monster.BP_Monster_C");
	UClass* LoadedClass = StaticLoadClass(AActor::StaticClass(), nullptr, *Path);

	if (LoadedClass)
	{

		FTransform Trans;
		AMonster* NewActor = GetWorld()->SpawnActorDeferred<AMonster>(LoadedClass, Trans);
		NewActor->SetDataKey(_ItemName);

		Trans.SetLocation(_OriginPos);
		NewActor->FinishSpawning(Trans);
		AllMonster.Add(NewActor);

		return NewActor;
	}
	else return nullptr;
}

void UMonsterManager::NetSyncMonster()
{
}


// Called when the game starts
void UMonsterManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMonsterManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

