#include "MyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "StarItem.h"
#include "MyGameInstance.h"

AMyGameState::AMyGameState()
{
	Score = 0;
	TargetLevelScore = 100;
	CurrentLevelScore = 0;
	TargetWaveScore = 30;
	CurrentWaveScore = 0;
	WaveDuration = 60.0f;
	WaveBreakTime = 10.0f;
	CurrentWaveCount = 0;
	MaxWaves = 3;
	CurrentLevelIndex = 0;
	MaxLevels = 3;
}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();
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
	CurrentLevelScore += Amount;
}

int32 AMyGameState::GetTargetLevelScore() const
{
	return TargetLevelScore;
}

int32 AMyGameState::GetCurrentLevelScore() const
{
	return CurrentLevelScore;
}

void AMyGameState::StartLevel()
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		if (MyGameInstance)
		{
			CurrentLevelIndex = MyGameInstance->CurrentLevelIndex;
		}
	}
	TargetLevelScore = 100;
	TargetWaveScore = 30;
	CurrentLevelScore = 0;
	CurrentWaveCount = 0;
	StartWave();
}

void AMyGameState::StartWave()
{
	// 웨이브 확인
	if (CurrentWaveCount >= MaxWaves)
	{
		UE_LOG(LogTemp, Warning, TEXT("모든 웨이브 종료!"));
		OnCompleteLevelScore();
		return;
	}

	CurrentWaveCount++;
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
	if (CurrentWaveScore < TargetWaveScore)
	{
		OnGameOver();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("웨이브 종료! 휴식 시작."));

		// 10초 휴식 후 다시 StartWave를 호출하도록 타이머 설정
		GetWorldTimerManager().SetTimer(
			WaveTimerHandle,
			this,
			&AMyGameState::StartWave,
			WaveBreakTime,
			false
		);
		// 웨이브 시간 감소
		WaveDuration -= 15.0f;
	}
}

void AMyGameState::OnCompleteLevelScore()
{
	if (CurrentLevelScore >= TargetLevelScore)
	{
		UE_LOG(LogTemp, Warning, TEXT("목표 점수 달성"));

		EndLevel();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("목표 점수 부족"));

		OnGameOver();
	}
}

void AMyGameState::EndWave()
{
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
	UE_LOG(LogTemp, Warning, TEXT("게임 오버"));
}