#include "CopperStarItem.h"

ACopperStarItem::ACopperStarItem()
{
	PointValue = 1;
	ItemType = "CopperStar";
}

void ACopperStarItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}