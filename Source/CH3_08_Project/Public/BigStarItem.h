#pragma once

#include "CoreMinimal.h"
#include "StarItem.h"
#include "BigStarItem.generated.h"

UCLASS()
class CH3_08_PROJECT_API ABigStarItem : public AStarItem
{
	GENERATED_BODY()
	
public:
	ABigStarItem();

	virtual void ActivateItem(AActor* Activator) override;
};
