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
	// ½ºÅ¸ È¹µæ ½Ã ¾òÀ» Á¡¼ö
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 PointValue;
};
