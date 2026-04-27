#include "HealingItem.h"

AHealingItem::AHealingItem()
{
	HealAmount = 30.0f;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("%d Healing"), HealAmount));

	DestroyItem();
}