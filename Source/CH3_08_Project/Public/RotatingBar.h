#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingBar.generated.h"

class URotatingMovementComponent;

UCLASS()
class CH3_08_PROJECT_API ARotatingBar : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotatingBar();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bar")
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bar")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bar")
	URotatingMovementComponent* RotatingComponent;
};
