// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"
#include "MonsterAIController.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "Engine/DataTable.h"
#include "Monster/MonsterDataTable.h"
#include "Engine/SkeletalMesh.h"
#include "Monster/MonsterAnimInstance.h" // Add this include to resolve UMonsterAnimInstance
#include <Net/UnrealNetwork.h>


// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true; 



	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnComponentBeginOverlap);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	// �ӽ÷� ������ ���̺� �ҷ�����
	FString DataPath = TEXT("/Game/Blueprints/Monster/Data/DT_MonsterDataTable.DT_MonsterDataTable");
	ConstructorHelpers::FObjectFinder<UDataTable> FinderDataTables(*DataPath);



	if (true == FinderDataTables.Succeeded())
	{
		MonsterDataTable = FinderDataTables.Object;
	}

	
	
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{

	if (GetWorld()->GetAuthGameMode())
	{
		int a = 0;
	}
	else
	{
		int a = 0;
	}

	if (DataKey == TEXT("") || true == DataKey.IsEmpty())
	{
		//(GMLOG, Error, TEXT("%S(%u)> if (ItemDataKey == TEXT("") || true == ItemDataKey.IsEmpty())"), __FUNCTION__, __LINE__);
		return;
	}

	if (nullptr != MonsterDataTable)
	{
		Data = MonsterDataTable->FindRow<FMonsterDataRow>(*DataKey, nullptr);
	}

	// ���� �ʿ�
	const FMonsterDataRow* FindData = Data;

	if (nullptr == FindData) return;
	
	AMonsterAIController* Con = Cast<AMonsterAIController>(GetController());

	if (nullptr != Con)
	{
		AIData = NewObject<UAIDataObject>(this);
		AIData->PlayData.Data = FindData->AIData;
		AIData->PlayData.SelfAnimPawn = this;
		AIData->PlayData.SelfPawn = this;
		AIData->PlayData.OriginPos = GetActorLocation();

		// BlackBoard�� AIData �������ֱ�
		Con->GetBlackboardComponent()->SetValueAsObject(TEXT("AIData"), AIData);

	}




	

	GetMesh()->SetSkeletalMesh(FindData->Mesh);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(FindData->AnimationBluePrint);


   
    UMonsterAnimInstance* CurAnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
    if (nullptr != CurAnimInstance)
    {
		for (auto AnimPair : FindData->Animations)
		{
			CurAnimInstance->AnimMontages.Add(static_cast<int>(AnimPair.Key), AnimPair.Value);
		}

		if (nullptr != Con)
		{
			AIData->PlayData.MonsterAnimInstance = CurAnimInstance;
		}
    }   

	//ChangeAnimation_Multicast()
	Super::BeginPlay();

	NetSyncMonster();
	
}
void AMonster::NetSyncMonster()
{

	int CurAnimation = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance())->GetCurAnimationType();

	ChangeAnimation_Multicast(CurAnimation);


}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMonster, DataKey);
}

void AMonster::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AMonster::ChangeAnimation_Implementation(int _CurAnimnation, FName _SectionName)
{

	ChangeAnimation_Multicast(_CurAnimnation, _SectionName);
}

void AMonster::ChangeAnimation_Multicast_Implementation(int _CurAnimnation, FName _SectionName)
{
	UMonsterAnimInstance* CurAnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());

	if (nullptr != CurAnimInstance)
	{
		CurAnimInstance->ChangeAnimation(_CurAnimnation, _SectionName);
	}
}
