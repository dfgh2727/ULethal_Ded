// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Items/Item.h"

#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Level/Items/ItemDataTable.h"
#include "Level/Items/ItemWidget.h"

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


	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(DefaultSceneRoot);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize({ 1000.f, 1000.f });
	WidgetComponent->SetTwoSided(true);
	WidgetComponent->SetRelativeScale3D({0.25f, 0.25f, 0.25f});

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	SetItemInfo();
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
				ItemName = Row->ItemName;
				ItemPrice = Row->ItemPrice;
				ItemGripType = Row->GripType;
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