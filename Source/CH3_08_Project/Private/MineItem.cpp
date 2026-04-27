#include "MineItem.h"

AMineItem::AMineItem()
{
	Damage = 10.0f;
	ItemType = "Mine";
}

void AMineItem::BeginPlay()
{
	Super::BeginPlay();

	float RandomScale = FMath::FRandRange(0.5f, 1.5f);

	if (RootComponent)
	{
		RootComponent->SetRelativeScale3D(FVector(RandomScale));
	}
}

void AMineItem::ActivateItem(AActor* Activator)
{
	DestroyItem();
}