#include "MyGameMode.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"
#include "MyGameState.h"

AMyGameMode::AMyGameMode()
{
	// MyChracter 스폰
	DefaultPawnClass = AMyCharacter::StaticClass();
	// MyPlayerController 사용
	PlayerControllerClass = AMyPlayerController::StaticClass();
	// MyGameStateBase 사용
	GameStateClass = AMyGameState::StaticClass();
}