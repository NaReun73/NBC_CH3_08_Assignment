#include "MyGameMode.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"

AMyGameMode::AMyGameMode()
{
	// MyChracter 스폰
	DefaultPawnClass = AMyCharacter::StaticClass();
	// MyPlayerController 사용
	PlayerControllerClass = AMyPlayerController::StaticClass();
}