#include "StarItem.h"
#include "Engine/World.h"
#include "MyGameState.h"

AStarItem::AStarItem()
{

}

void AStarItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		// 현재 게임의 월드를 가져옴
		if (UWorld* World = GetWorld())
		{
			// 현재 게임 월드의 GameState를 가져옴
			if (AMyGameState* GameState = World->GetGameState<AMyGameState>())
			{
				GameState->AddScore(PointValue);
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("%d Point"), PointValue));
			}
		}
	}

	DestroyItem();
}