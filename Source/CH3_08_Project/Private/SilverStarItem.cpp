#include "SilverStarItem.h"

ASilverStarItem::ASilverStarItem()
{
	PointValue = 3;
	ItemType = "SilverStar";
}

void ASilverStarItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}