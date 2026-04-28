#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

UCLASS()
class CH3_08_PROJECT_API AMyGameState : public AGameState
{
	GENERATED_BODY()
public:
	AMyGameState();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;

	// 레벨 목표 점수
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 TargetLevelScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 CurrentLevelScore;*/
	// 웨이브 목표 점수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 TargetWaveScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 CurrentWaveScore;

	// 각 Wave가 유지되는 시간
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	float WaveDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	float WaveBreakTime;
	// 현재 웨이브
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWaveCount;
	// 최대 웨이브 수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 MaxWaves;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	bool BreakTime;

	// 현재 진행 중인 레벨 인덱스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	// 전체 레벨의 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;
	// 실제 레벨 맵 이름. 인덱스를 차례대로 연동
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	//매 레벨이 끝나기 전까지 시간이 흐르도록 관리하는 타이머
	//FTimerHandle LevelTimerHandle;
	// 웨이브 끝나기 전까지 시간이 흐르도록 관리하는 타이머
	FTimerHandle WaveTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;

	

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

	// 게임이 완전히 끝났을 때 (모든 레벨 종료) 실행되는 함수
	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();

	// 레벨을 시작할 떄, 아이템 스폰 및 타이머 설정
	void StartLevel();
	// 웨이브 시작
	void StartWave();
	// 웨이브 제한 시간이 끝났을 때
	void OnWaveTimeUp();
	// 별을 획득했을 떄
	void OnCompleteWaveScore();
	// 웨이브 종료
	void EndWave();
	// 레벨을 강제 종료하고 다음 레벨로 이동
	void EndLevel();
	// HUD 없데이트
	void UpdateHUD();
};
