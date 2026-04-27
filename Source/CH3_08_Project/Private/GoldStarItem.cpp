#include "GoldStarItem.h"

AGoldStarItem::AGoldStarItem()
{
	PointValue = 5;
	ItemType = "GoldStar";
}

void AGoldStarItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}