// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Items/Weapon.h"
#include "Components/BoxComponent.h"
#include "Monster/Monster.h"

AWeapon::AWeapon()
{
	HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	HitBox->SetupAttachment(StaticMeshComponent);
    HitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    HitBox->SetCollisionObjectType(ECC_WorldDynamic);
    HitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
}


void AWeapon::BeginPlay()
{
	AItem::BeginPlay();

    if (HitBox)
    {
        HitBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OverlapHitBoxBegin);
        HitBox->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OverlapHitBoxEnd);
    }
}

void AWeapon::Tick(float DeltaTime)
{
	AItem::Tick(DeltaTime);

}



void AWeapon::OverlapHitBoxBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    if (OtherActor != nullptr && OtherActor != this)
    {
        AMonster* Monster = Cast<AMonster>(OtherActor);
        if (Monster != nullptr)
        {
            bHit = true;
        }
    }
}

void AWeapon::OverlapHitBoxEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    bHit = false;
}

void AWeapon::EnableHitBox()
{
    if (HitBox)
    {

        HitBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
        bHit = false;
    }
}

void AWeapon::DisableHitBox()
{
    if (HitBox)
    {
        HitBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

        bHit = false;
    }
}
