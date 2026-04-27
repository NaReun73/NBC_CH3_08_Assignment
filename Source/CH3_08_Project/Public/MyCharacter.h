#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;	// 스프링 암 컴포넌트 전방선언
class UCameraComponent;		// 카메라 컴포넌트 전방선언
struct FInputActionValue;	// Enhanced Input 약션 값을 받을 떄 사용하는 구조체

UCLASS()
class CH3_08_PROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

	// 스프링 암 컴포넌트
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	// 카메라 컴포넌트
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

protected:
	// 채력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	// IA_Move와 IA_Jump 등을 처리할 함수 원형
	// Enhanced Input에서 액션 값은 FInputActionValue로 전달
	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);

	void OnDeath();
public:
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);
};
