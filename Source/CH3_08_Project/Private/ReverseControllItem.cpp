#include "ReverseControllItem.h"
#include "MyCharacter.h"

AReverseControllItem::AReverseControllItem()
{
	Duration = 5.0f;
	ItemType = "ReverseControllItem";
}

void AReverseControllItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(Activator))
		{
			PlayerCharacter->ApplyReverseControl(Duration);
		}
	}

	DestroyItem();
}