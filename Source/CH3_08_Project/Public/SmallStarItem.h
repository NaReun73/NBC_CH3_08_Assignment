#pragma once

#include "CoreMinimal.h"
#include "StarItem.h"
#include "SmallStarItem.generated.h"

UCLASS()
class CH3_08_PROJECT_API ASmallStarItem : public AStarItem
{
	GENERATED_BODY()
	
public:
	ASmallStarItem();

	virtual void ActivateItem(AActor* Activator) override;
};
