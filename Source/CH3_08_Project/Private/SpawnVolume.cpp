#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);
}

void ASpawnVolume::SpawnRandomItem()
{
	if (FItemSpawnRow* SelectedRow = GetRandomItem())
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			SpawnItem(ActualClass);
		}
	}
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	// 박스 컴포넌트의 스케일된 Extent, x/y/z 방향으로 반지름을 구함
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	// 박스 중심 위치
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	// 각 축별로 무작위 값 생성
	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z));
}

FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	if (!ItemDataTable) return nullptr;

	// 모든 Row(행) 가져오기
	TArray<FItemSpawnRow*> AllRows;
	static const FString ConextString(TEXT("ItemPawnContext"));
	ItemDataTable->GetAllRows(ConextString, AllRows);

	if (AllRows.IsEmpty()) return nullptr;

	// 전체 확률 합 구하기
	float TotalChance = 0.0f; // 초기화

	for (const FItemSpawnRow* Row : AllRows)
	{
		// Row가 유효한지 확인
		if (Row)
		{
			TotalChance += Row->Spawnchane;
		}
	}

	const float RandValue = FMath::FRandRange(0.0f, TotalChance);
	float AccumulateChance = 0.0f;

	// 누적 확률로 아이템 선택
	for (FItemSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->Spawnchane;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}

	return nullptr;
}

void ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass)return;

	GetWorld()->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointInVolume(),
		FRotator::ZeroRotator
	);
}