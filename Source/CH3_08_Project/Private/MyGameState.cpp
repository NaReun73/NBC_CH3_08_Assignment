#include "MyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "StarItem.h"
#include "MyGameInstance.h"
#include "MyPlayerController.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

AMyGameState::AMyGameState()
{
	Score = 0;
	TargetWaveScore = 5;
	CurrentWaveScore = 0;
	WaveDuration = 60.0f;
	WaveBreakTime = 1.0f;
	BreakTime = false;
	CurrentWaveCount = 0;
	MaxWaves = 3;
	CurrentLevelIndex = 0;
	MaxLevels = 3;
}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&AMyGameState::UpdateHUD,
		0.1f,
		true
	);
}

int32 AMyGameState::GetScore() const
{
	return Score;
}

void AMyGameState::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		if (MyGameInstance)
		{
			MyGameInstance->AddToScore(Amount);
		}
	}
	CurrentWaveScore += Amount;
}

void AMyGameState::StartLevel()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController))
		{
			MyPlayerController->ShowGameHUD();
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		if (MyGameInstance)
		{
			CurrentLevelIndex = MyGameInstance->CurrentLevelIndex;
		}
	}

	TargetWaveScore = 5;
	CurrentWaveCount = 0;
	StartWave();
}

void AMyGameState::StartWave()
{
	// 웨이브 확인
	if (CurrentWaveCount >= MaxWaves)
	{
		UE_LOG(LogTemp, Warning, TEXT("모든 웨이브 종료!"));
		EndLevel();
		return;
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		if (MyGameInstance)
		{
			CurrentWaveCount++;
			MyGameInstance->CurrentWaveIndex = CurrentWaveCount;
		}
	}

	BreakTime = false;
	UE_LOG(LogTemp, Warning, TEXT("웨이브 %d 시작!"), CurrentWaveCount);

	// 웨이브 지속 시간 만큼 타이머 설정
	GetWorldTimerManager().SetTimer(
		WaveTimerHandle,
		this,
		&AMyGameState::OnWaveTimeUp,
		WaveDuration,
		false
	);
}

void AMyGameState::OnWaveTimeUp()
{
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	// 목표 점수 달성 확인
	if (CurrentWaveScore < TargetWaveScore)
	{
		OnGameOver();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("웨이브 종료! 휴식 시작."));

		BreakTime = true;

		// 10초 휴식 후 다시 StartWave를 호출하도록 타이머 설정
		GetWorldTimerManager().SetTimer(
			WaveTimerHandle,
			this,
			&AMyGameState::StartWave,
			WaveBreakTime,
			false
		);
		// 웨이브 시간 감소
		WaveDuration -= 10.0f;
		CurrentWaveScore = 0;
	}
}

void AMyGameState::OnCompleteWaveScore()
{
	if (CurrentWaveScore >= TargetWaveScore)
	{
		UE_LOG(LogTemp, Warning, TEXT("클리어 조건 달성! 웨이브 클리어"));
		OnWaveTimeUp();
	}
	/*else
	{
		UE_LOG(LogTemp, Warning, TEXT("웨이브 클리어 실패"));

		OnGameOver();
	}*/
}

void AMyGameState::EndLevel()
{
	// 타이머 해제
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		if (MyGameInstance)
		{
			AddScore(Score);
			CurrentLevelIndex++;
			MyGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	// 모든 레벨을 다 돌았으면 게임 오버
	if (CurrentLevelIndex >= MaxLevels)
	{
		UE_LOG(LogTemp, Warning, TEXT("모든 레벨 완료"));

		OnGameOver();
		return;
	}

	// 레벨 맵 이름이 있으면 해당 맵 불러오기
	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("다음 레벨 이동"));

		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("해당 레벨 없음"));

		// 맵 이름이 없으면 게임오버
		OnGameOver();
	}
}

void AMyGameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController))
		{
			MyPlayerController->SetPause(true);
			MyPlayerController->ShowMainMenu(true);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("게임 오버"));
}

void AMyGameState::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController);
		
		if (UUserWidget* HUDWidget = MyPlayerController->GetHUDWidget())
		{
			if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
			{
				float RemainingTime = GetWorldTimerManager().GetTimerRemaining(WaveTimerHandle);
				TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time : %.1f"), RemainingTime)));
			}

			if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("TargetScore"))))
			{
				if (UGameInstance* GameInstance = GetGameInstance())
				{
					UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);

					if (MyGameInstance)
					{
						ScoreText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentWaveScore, TargetWaveScore)));
					}
				}
			}

			if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
			{
				LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level : %d"), CurrentLevelIndex+1)));
			}

			if (UTextBlock* WaveIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Wave"))))
			{
				if (BreakTime)
				{
					WaveIndexText->SetText(FText::FromString(FString::Printf(TEXT("BrakeTime"))));
				}
				else
				{
					WaveIndexText->SetText(FText::FromString(FString::Printf(TEXT("Wave : %d"), CurrentWaveCount)));
				}
			}
		}
	}
}