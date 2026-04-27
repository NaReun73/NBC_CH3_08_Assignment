#pragma once

#include "CoreMinimal.h"
#include "StarItem.h"
#include "SilverStarItem.generated.h"

UCLASS()
class CH3_08_PROJECT_API ASilverStarItem : public AStarItem
{
	GENERATED_BODY()
	
public:
	ASilverStarItem();

	virtual void ActivateItem(AActor* Activator) override;
};
