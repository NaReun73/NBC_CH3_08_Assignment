#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "StarItem.generated.h"

UCLASS()
class CH3_08_PROJECT_API AStarItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AStarItem();

protected:
	// 스타 획득 시 얻을 점수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 PointValue;

	virtual void ActivateItem(AActor* Activator) override;
};
