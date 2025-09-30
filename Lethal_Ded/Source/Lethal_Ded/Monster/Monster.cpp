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
#include <Global/LCConst.h>
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/SceneComponent.h"
#include "TimerManager.h" // �߰�: Ÿ�̸� ���



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

	ChangeAnimation_Implementation(CurAnimation);


}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AMonsterAIController* Con = Cast<AMonsterAIController>(GetController());
	if (nullptr != Con)
	{
		UObject* Object= Con->GetBlackboardComponent()->GetValueAsObject("AIData");

		AIStateValue= Cast<UAIDataObject>(Object)->PlayData.AIState;

	}
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
	DOREPLIFETIME(AMonster, AIStateValue);
	DOREPLIFETIME(AMonster, bIsWaitTime);

	DOREPLIFETIME(AMonster, bIsDead);
	DOREPLIFETIME(AMonster, CurrentAttackCount);
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

void AMonster::OnRep_IsDead()
{
	if (bIsDead)
	{
		HandleDeath(nullptr);
	}
}

void AMonster::S2C_OnKilled_Implementation(AActor* Killer)
{
	HandleDeath(Killer);
}

void AMonster::AttackStart()
{
	GetMesh()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName, true);
}

void AMonster::AttackEnd()
{
	GetMesh()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName, true);

	FName SocketName = TEXT("PlayerPointSocket");

	TArray<AActor*> Attached;
	GetAttachedActors(Attached, /*bResetArray=*/true);

	for (AActor* ChildActor : Attached)
	{
		if (!ChildActor) continue;

		if (AActor* Root = ChildActor)
		{
			if (Root->GetAttachParentActor() == this && Root->GetAttachParentSocketName() == SocketName)
			{
				if (nullptr != Cast<ACharacter>(Root))
				{
					// ĳ���� ����
					bIsWaitTime = true;
				}
			}
		}
	}
}
void AMonster::HandleDeath(AActor* Killer)
{

	// ���� �ð� �� ���� (�ʿ� ��)
	if (HasAuthority())
	{
		FTimerHandle DestroyTimerHandle;
		TWeakObjectPtr<AActor> WeakThis(this);

		FTimerDelegate DestroyDelegate = FTimerDelegate::CreateLambda([WeakThis]()
		{
			if (WeakThis.IsValid())
			{
				WeakThis->Destroy(true);
			}
		});

		GetWorldTimerManager().SetTimer(DestroyTimerHandle, DestroyDelegate, 5.0f, false);
	}
}
float AMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// ���� �θ� ó��(����/������ Ÿ�� �� ���� �⺻ ó��)
	const float Actual = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	// ���������� ����/��� ó��
	if (!HasAuthority() || bIsDead)
	{
		return Actual;
	}

	// �������� 0 ���϶�� ����(���ϸ� ���� ����)
	if (Damage <= 0.f)
	{
		return Actual;
	}

	// ���� 1ȸ�� ī��Ʈ
	++CurrentAttackCount;

	// �Ӱ�ġ ���� �� ��� ó��
	if (CurrentAttackCount >= AttacksToKill)
	{
		bIsDead = true;
		HandleDeath(DamageCauser ? DamageCauser : (EventInstigator ? EventInstigator->GetPawn() : nullptr));
		S2C_OnKilled(DamageCauser ? DamageCauser : (EventInstigator ? EventInstigator->GetPawn() : nullptr));
	}

	return Actual;
}
void AMonster::C2S_AttachCharacter_Implementation(AActor* Target)
{
	S2C_ApplyCaptured_Implementation(Target, true);
}

void AMonster::S2C_ApplyCaptured_Implementation(AActor* Target, bool bCaptured)
{
	const FName SocketName = TEXT("PlayerPointSocket");
	//const FAttachmentTransformRules KeepWorld(EAttachmentRule::KeepWorld, true);

	//const FTransform SocketW = GetMesh()->GetSocketTransform(SocketName, RTS_World);


	if (GetMesh()->DoesSocketExist(SocketName))
	{
		// 1) ������ ���� ��ġ/ȸ���� ����ϰ�, ����� ���� ������ ����
		const FTransform SocketW = GetMesh()->GetSocketTransform(SocketName, RTS_World);
		const FVector    OrigScale = Target->GetActorScale3D();
		const FTransform DesiredWorld(
			SocketW.GetRotation(),
			SocketW.GetLocation(),
			OrigScale // �������� ���� ����
		);

		// 2) �θ� ������ ���ĸ� ����(�����ϸ� ���밪����)
		USceneComponent* TargetRootComp = Target->GetRootComponent();
		if (!TargetRootComp) return;
		TargetRootComp->SetAbsolute(false, false, true); // ��ġ/ȸ���� �θ� ������, �������� ����

		// 3) ���� ���� Ʈ�������� ���� ��
		Target->SetActorTransform(DesiredWorld, false, nullptr, ETeleportType::TeleportPhysics);

		// 4) KeepWorld ��Ģ���� ���Ͽ� ����ġ
		const FAttachmentTransformRules KeepWorld(
			EAttachmentRule::KeepWorld,
			EAttachmentRule::KeepWorld,
			EAttachmentRule::KeepWorld,
			/*bWeldSimulatedBodies=*/true
		);
		TargetRootComp->AttachToComponent(GetMesh(), KeepWorld, SocketName);

		if (bCaptured)
		{
			ACharacter* Char = Cast<ACharacter>(Target);

		
			if ( Char->GetCharacterMovement())
			{
				auto* Move = Char->GetCharacterMovement();
				Move->StopMovementImmediately();
				Move->DisableMovement();
				Move->NetworkSmoothingMode = ENetworkSmoothingMode::Disabled;
			}
			Char->SetReplicateMovement(false);
			//Cast<ACharacter>(Target)->GetCharacterMovement()->SetMovementMode(bCaptured ? EMovementMode::MOVE_None : EMovementMode::MOVE_Walking);


			USceneComponent* RootComp = Target->GetRootComponent();

			UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(RootComp);


			if (PrimitiveComp != nullptr)
			{
				// 3. ��Ʈ ������Ʈ�� �ݸ��� ���� ����
				//PrimitiveComp->SetIsReplicated(true);
				PrimitiveComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}
		//S2C_ApplyCaptured(Target, true);
	}
	else
	{
		// �α�: ������ ã�� �� �����ϴ�.
		UE_LOG(LogTemp, Warning, TEXT("Socket 'PlayerPointSocket' not found on monster mesh!"));
	}

		

	

}
