#include "BigStarItem.h"

ABigStarItem::ABigStarItem()
{
	PointValue = 30;
	ItemType = "BigStar";
}

void ABigStarItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}