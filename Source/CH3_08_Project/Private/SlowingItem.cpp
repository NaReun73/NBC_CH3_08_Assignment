#include "SlowingItem.h"
#include "MyCharacter.h"

ASlowingItem::ASlowingItem()
{
	Duration = 5.0f;
	PenaltyMultiplier = 0.5f;
	ItemType = "SlowingItem";
}

void ASlowingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(Activator))
		{
			// Duration 시간 동안, PenaltyMultiplier 감소 적용
			PlayerCharacter->ApplySlowEffect(Duration, PenaltyMultiplier);
		}
	}

	DestroyItem();
}