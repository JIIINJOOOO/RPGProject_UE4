// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "GameFramework/Character.h"
#include "PalaceRampageMonster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate); // 공격 태스크에서 몬스터 공격 종료되면 알림 받을 수 있도록 델리게이트

UCLASS()
class PROJECTRPG_API APalaceRampageMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APalaceRampageMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// 캐릭터 스탯
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UAdamCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	void Attack();
	FOnAttackEndDelegate OnAttackEnd;
	void AttackCheck();
	void Die();
	void MakeRagdollWithImpulse();
private:
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsAttacking;

	UPROPERTY()
	class URampageAnimInstance* RampageAnim;

	FTimerHandle destroyTimerHandle; // 객체 소멸 위한 타이머 핸들
	float destroyInterval; // 객체 소멸될 때 까지 시간
};
