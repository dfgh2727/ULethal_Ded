// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Items/Item.h"

#include "Level/Items/ItemWidget.h"

#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextBlock.h"


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;


	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = DefaultSceneRoot;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(DefaultSceneRoot);

	GrabTrigger = CreateDefaultSubobject<UBoxComponent>("GrabTrigger");
	GrabTrigger->SetupAttachment(DefaultSceneRoot);
	GrabTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GrabTrigger->SetCollisionObjectType(ECC_WorldDynamic);
	GrabTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	GrabTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(DefaultSceneRoot);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize({ 1000.f, 1000.f });
	WidgetComponent->SetTwoSided(true);
	WidgetComponent->SetRelativeScale3D({0.25f, 0.25f, 0.25f});

	Tags.Add("Item");
}


// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	SetItemInfo();


	GrabTrigger->OnComponentBeginOverlap.AddDynamic(this, &AItem::OverlapBegin);
	GrabTrigger->OnComponentEndOverlap.AddDynamic(this, &AItem::OverlapEnd);


}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetWidgetRotation();


	if (bWidgetVisible == true)
	{
		WidgetComponent->SetVisibility(true);
	}
	else
	{
		WidgetComponent->SetVisibility(false);
	}

}

void AItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);


	if (GrabTrigger)
	{
		FString BPItemName = GetName();
		BPItemName.RemoveFromStart("BP_");
		GrabTrigger->ComponentTags.AddUnique(FName(*BPItemName));
	}
}


void AItem::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bGrabbable = true;
}

void AItem::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bGrabbable = false;
}

void AItem::SetItemInfo()
{
	if (ItemDataTable != nullptr)
	{
		TArray<FItemDataRow*> AllRows;
		ItemDataTable->GetAllRows(TEXT("ItemInfo"), AllRows);

		for (FItemDataRow* Row : AllRows)
		{
			if (Row && Row->ItemList == GetClass()) // 현재 아이템 BP 클래스와 동일하면
			{
				ItemDataRow = Row;

				ItemName = Row->ItemName;
				ItemPrice = Row->ItemPrice;
				ItemGripType = Row->GripType;
				ItemInteractType = Row->Interact;
				break;
			}
		}
	}

	if (UUserWidget* Widget = WidgetComponent->GetUserWidgetObject())
	{
		if (UTextBlock* NameText = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("ItemName"))))
		{
			NameText->SetText(FText::FromString(ItemName));
		}

		if (UTextBlock* PriceText = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("Price"))))
		{
			PriceText->SetText(FText::AsNumber(ItemPrice));
		}
	}
}


void AItem::SetWidgetRotation()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{

		if (PC->PlayerCameraManager)
		{
			FVector CamLocation = PC->PlayerCameraManager->GetCameraLocation();
			FVector ToCam = CamLocation - WidgetComponent->GetComponentLocation();

			FRotator LookAtRotation = FRotationMatrix::MakeFromX(ToCam).Rotator();
			WidgetComponent->SetWorldRotation(LookAtRotation);

			float Distance = ToCam.Size();

			if (Distance > ITEMSHOWDISTANCE)
			{
				bWidgetVisible = false;
			}
			else
			{
				bWidgetVisible = true;

			}
		}
	}

}
