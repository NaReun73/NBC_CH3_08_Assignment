#include "BaseItem.h"
#include "Components/SphereComponent.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	// 루트 컴포넌트 생성 및 설정
	//Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	//SetRootComponent(Scene);

	// 충돌 컴포넌트 생성 및 설정
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	// 루프 컴포넌트로 설정
	SetRootComponent(Collision);
	// 기본 반지름 200로 설정
	Collision->InitSphereRadius(200.0f);
	// 겹침만 감지하는 프로파일 설정
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	// 물리 시뮬레이션 활성화
	Collision->SetSimulatePhysics(true);
	// 충돌 프리셋 설정(물리 액터로 설정)
	//Collision->SetCollisionProfileName(TEXT("PhysicsActor"));
	// 물리 엔진 활성화
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// 바닥(Static)에만 충돌하도록 설정
	Collision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	

	// 스태틱 메시 컴포넌트 생성 및 설정
	// Collision을 시각적으로 보여주기 위한 메시
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);
	// 물리 연산에 영향을 주지않도록 설정
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 어떤 아이템인지 보여주기 위한 메시
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(StaticMesh);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Overlap 이벤트 바인딩
	// 플레이어가 범위위 안에 들어올 떄 자동으로 OnItemOverlap을 호출
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);
}

void ABaseItem::OnItemOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// OtherActor가 플레이어인지 확인 ("Player" 태그 활용)
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap")));
		ActivateItem(OtherActor);
	}
}

void ABaseItem::OnItemEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("EndOverlap")));
}

void ABaseItem::ActivateItem(AActor* Activator)
{

}

FName ABaseItem::GetItemType() const
{
	return ItemType;
}

void ABaseItem::DestroyItem()
{
	// AActor에서 제공하는 함수로 객체 제거
	Destroy();
}

