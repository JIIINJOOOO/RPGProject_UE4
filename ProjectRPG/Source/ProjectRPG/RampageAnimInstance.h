// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "Animation/AnimInstance.h"
#include "RampageAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class PROJECTRPG_API URampageAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	URampageAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // tick
public:
	void PlayRandAttackMontage(); // 공격 몽타주 재생
	void SetRandAtkAnimIdx() { RandAtkAnimIdx = FMath::RandRange(0, 2); }
	void SetDeadAnim() { bIsDead = true; }
public:
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	
private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnDir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsDead;  // 죽는 애니메이션 재생 위한 변수
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	int32 RandAtkAnimIdx; // 랜덤 공격 애니메이션 위한 인덱스

	// Montages
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : 블루프린트 편집 화면에서만 보여짐
	UAnimMontage* AttackMontage_1;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : 블루프린트 편집 화면에서만 보여짐
	UAnimMontage* AttackMontage_2;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : 블루프린트 편집 화면에서만 보여짐
	UAnimMontage* AttackMontage_3;
};
