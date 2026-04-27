#pragma once

#include "CoreMinimal.h"
#include "StarItem.h"
#include "CopperStarItem.generated.h"

UCLASS()
class CH3_08_PROJECT_API ACopperStarItem : public AStarItem
{
	GENERATED_BODY()

public:
	ACopperStarItem();

	virtual void ActivateItem(AActor* Activator) override;
};
