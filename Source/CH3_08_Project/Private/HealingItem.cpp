#include "HealingItem.h"
#include "MyCharacter.h"

AHealingItem::AHealingItem()
{
	HealAmount = 30.0f;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("%f Healing"), HealAmount));
		}
	}

	DestroyItem();
}