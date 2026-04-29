#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SlowingItem.generated.h"

UCLASS()
class CH3_08_PROJECT_API ASlowingItem : public ABaseItem
{
	GENERATED_BODY()
public:
	ASlowingItem();

	virtual void ActivateItem(AActor* Activator) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float PenaltyMultiplier;
};
