#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"

AMyPlayerController::AMyPlayerController()
	: InputMappingContext(nullptr),
	  MoveAction(nullptr),
	  JumpAction(nullptr),
	  LookAction(nullptr)
{

}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// 현재 PlayerController에 연결된 LocalPlayer 객체를 가져옴
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		// LocalPlayer에서 EnhancedInputLocalPlayerSubsystem을 획득
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{	
				// Subsystem을 통해 할당한 IMC 활성화
				// 우선순위는 0이 가장 높은 우선순위
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}