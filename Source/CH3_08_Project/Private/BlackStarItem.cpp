#include "BlackStarItem.h"

ABlackStarItem::ABlackStarItem()
{
	PointValue = -1;
	ItemType = "BlackStar";
}

void ABlackStarItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}