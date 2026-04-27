#pragma once

#include "CoreMinimal.h"
#include "StarItem.h"
#include "GoldStarItem.generated.h"

UCLASS()
class CH3_08_PROJECT_API AGoldStarItem : public AStarItem
{
	GENERATED_BODY()
	
public:
	AGoldStarItem();

	virtual void ActivateItem(AActor* Activator) override;
};
