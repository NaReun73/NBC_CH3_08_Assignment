#include "SmallStarItem.h"

ASmallStarItem::ASmallStarItem()
{
	PointValue = 10;
	ItemType = "SmallStar";
}

void ASmallStarItem::ActivateItem(AActor * Activator)
{
	DestroyItem();
}
