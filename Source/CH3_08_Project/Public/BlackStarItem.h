#pragma once

#include "CoreMinimal.h"
#include "StarItem.h"
#include "BlackStarItem.generated.h"

UCLASS()
class CH3_08_PROJECT_API ABlackStarItem : public AStarItem
{
	GENERATED_BODY()

public:
	ABlackStarItem();

	virtual void ActivateItem(AActor* Activator) override;
	
};
