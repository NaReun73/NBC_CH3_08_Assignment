#include "MineItem.h"

AMineItem::AMineItem()
{
	Damage = 10.0f;
	ItemType = "Mine";
}

void AMineItem::ActivateItem(AActor* Activator)
{
	DestroyItem();
}