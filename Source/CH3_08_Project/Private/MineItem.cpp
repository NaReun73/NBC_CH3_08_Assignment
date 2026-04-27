#include "MineItem.h"
#include "Kismet/GameplayStatics.h"

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
	if (Activator && Activator->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(
			Activator,
			Damage,
			nullptr,
			this,
			UDamageType::StaticClass()
		);
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("%f Damage"), Damage));
	}

	DestroyItem();
}