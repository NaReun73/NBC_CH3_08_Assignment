#include "StarItem.h"

AStarItem::AStarItem()
{

}

void AStarItem::ActivateItem(AActor* Activator)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("%d Point"), PointValue));

	DestroyItem();
}