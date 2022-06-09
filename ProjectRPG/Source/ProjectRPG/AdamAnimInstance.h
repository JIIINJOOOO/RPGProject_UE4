// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "Animation/AnimInstance.h"
#include "AdamAnimInstance.generated.h"

// 여러개의 함수가 등록되도록 멀티캐스트로 선언
DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnSwordTookOutDelegate);
DECLARE_MULTICAST_DELEGATE(FOnBowTookOutDelegate);
DECLARE_MULTICAST_DELEGATE(FOnBowAttackPickArrowDelegate);
DECLARE_MULTICAST_DELEGATE(FOnBowAttackShootArrowDelegate);




/**
 * 
 */
UCLASS()
class PROJECTRPG_API UAdamAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAdamAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // tick
	void PlayAttackMontage(EWeaponType curWeapon); // 공격 몽타주 재생
	void PlayChangeWeaponMontage(EWeaponType nextWeapon);
	void JumpToAttackMontageSection(int32 NewSection); // 칼 콤보공격

public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnSwordTookOutDelegate OnSwordTookOutCheck; // 칼,방패로 무기 교체
	FOnBowTookOutDelegate OnBowTookOutCheck; // 활로 무기 교체
	FOnBowAttackPickArrowDelegate OnBowPickArrowCheck;
	FOnBowAttackShootArrowDelegate OnBowShootArrowCheck;

	void SetDeadAnim() { bIsDead = true; }
	void SetSprintAnim(bool bPressedShift) { bIsSprinting = bPressedShift; }
	void SetUsingShieldAnim(bool bPressedRightClick) { bUsingShield = bPressedRightClick; }
	void SetAimingArrowAnim(bool bPressedRightClick) { bAimingArrow = bPressedRightClick; }
	void SetChangingWeapon(bool bPressedNumKey) { bIsChangingWeapon = bPressedNumKey; }
	bool GetbUsingShield() { return bUsingShield; }
	bool GetbAimingArrow() { return bAimingArrow; }
	bool GetbIsSprinting() { return bIsSprinting; }
	bool GetbIsChangingWeapon() { return bIsChangingWeapon; }
	

private:
	// 칼,방패로 무기 교체
	UFUNCTION()
	void AnimNotify_TookOutSword();
	// 활로 무기 교체
	UFUNCTION()
	void AnimNotify_TookOutBow();
	// 활 기본공격 노티파이
	UFUNCTION()
	void AnimNotify_PickArrow();
	UFUNCTION()
	void AnimNotify_ShootArrow();
	// 칼 콤보공격 체크 애님 노티파이
	UFUNCTION()
	void AnimNotify_AttackHitCheck(); 

	UFUNCTION()
	void AnimNotify_NextAttackCheck(); 

	FName GetAttackMontageSectionName(int32 Section);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta=(AllowPrivateAccess=true))
	float CurrentPawnSpeed;
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnDir;*/ // 캐릭터 진행 방향

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsDead;  // 죽는 애니메이션 재생 위한 변수
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	int32 RandDeathAnimIdx; // 랜덤 죽음 애니메이션 위한 인덱스

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsFalling;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsSprinting; // toggle shift

	// 무기 전환 상태
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsChangingWeapon;

	// 무기에 따라 다른 특수기능 - state machine으로 처리
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bUsingShield; // right click
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bAimingArrow; // right click

	

	// 몽타주들
	// SwordAndShield
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : 블루프린트 편집 화면에서만 보여짐
	UAnimMontage* AttackMontage; // 좌클릭 기본공격

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = WeaponChange, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : 블루프린트 편집 화면에서만 보여짐
	UAnimMontage* ChangeToSwordMontage;

	// Bow
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = WeaponChange, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : 블루프린트 편집 화면에서만 보여짐
	UAnimMontage* ChangeToBowMontage;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = WeaponChange, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : 블루프린트 편집 화면에서만 보여짐
	UAnimMontage* BowAttackMontage; // 좌클릭 기본공격
};
