#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ReverseControllItem.generated.h"

UCLASS()
class CH3_08_PROJECT_API AReverseControllItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AReverseControllItem();

	virtual void ActivateItem(AActor* Activator) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Duration;

};
