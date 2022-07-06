// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "AdamCharacter.h"
#include "Net/UnrealNetwork.h"


UAdamAnimInstance::UAdamAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	bIsFalling = false;
	bIsSprinting = false;
	bIsDead = false;
	bIsUsingShield = false;
	bIsAimingArrow = false;
	bIsChangingWeapon = false;
	// 랜덤 죽음 애니메이션 인덱스 세팅
	RandDeathAnimIdx = FMath::RandRange(0, 1);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SWORDATTACK_MTG(TEXT("/Game/PalaceWorld/Blueprints/Animations/AdamSwordComboMTG.AdamSwordComboMTG"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BOWATTACK_MTG(TEXT("/Game/PalaceWorld/Blueprints/Animations/AdamBowBasicAttackMTG.AdamBowBasicAttackMTG"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> CHANGETO_SWORD_MTG(TEXT("/Game/PalaceWorld/Blueprints/Animations/SS_WeaponOutMTG.SS_WeaponOutMTG"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> CHANGETO_BOW_MTG(TEXT("/Game/PalaceWorld/Blueprints/Animations/B_WeaponOutMTG.B_WeaponOutMTG"));


	if (SWORDATTACK_MTG.Succeeded())
	{
		AttackMontage = SWORDATTACK_MTG.Object;
	}
	if (BOWATTACK_MTG.Succeeded())
	{
		BowAttackMontage = BOWATTACK_MTG.Object;
	}
	if (CHANGETO_SWORD_MTG.Succeeded())
	{
		ChangeToSwordMontage = CHANGETO_SWORD_MTG.Object;
	}
	if (CHANGETO_BOW_MTG.Succeeded())
	{
		ChangeToBowMontage = CHANGETO_BOW_MTG.Object;
	}
	

}


void UAdamAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Player = Cast<AAdamCharacter>(TryGetPawnOwner());
	if (!::IsValid(Player))
		return;

	if (!bIsDead)
	{
		CurrentPawnSpeed = Player->GetVelocity().Size();
		//CurrentPawnDir = CalculateDirection(Pawn->GetVelocity(), FRotator(0.0f, Pawn->GetControlRotation().Yaw, 0.0f)); // pawn의 진행방향 구하는 코드	
		bIsFalling = Player->GetMovementComponent()->IsFalling(); // 캐릭터 컴포넌트에서만 사용 가능
		bIsSprinting = Player->IsSprinting();
		bIsUsingShield = Player->IsUsingShield();
		bIsAimingArrow = Player->IsAimingArrow();
	}

}

void UAdamAnimInstance::PlayAttackMontage(EWeaponType curWeapon)
{
	if (bIsDead)
		return;
	if (curWeapon == EWeaponType::E_SWORDSHIELD)
	{
		Montage_Play(AttackMontage, 1.0f);
	}
	else if (curWeapon == EWeaponType::E_BOW)
	{
		Montage_Play(BowAttackMontage, 1.0f);
	}
	
}


void UAdamAnimInstance::PlayChangeWeaponMontage(EWeaponType nextWeapon)
{
	if (nextWeapon == EWeaponType::E_SWORDSHIELD)
	{
		Montage_Play(ChangeToSwordMontage, 1.0f);
	}
	else if (nextWeapon == EWeaponType::E_BOW)
	{
		Montage_Play(ChangeToBowMontage, 1.0f);
	}
}

void UAdamAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	if (!bIsDead)
	{
		if (Montage_IsPlaying(AttackMontage)) // 칼 콤보 공격 몽타주가 재생중이라면
		{
			Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
		}
	}
}

void UAdamAnimInstance::SetSprintAnim(bool bPressedShift)
{
	 bIsSprinting = bPressedShift;
	 //UE_LOG(PalaceWorld, Error, TEXT("AnimInstance IsSetSprinting = %d"),bIsSprinting); 
}

//bool UAdamAnimInstance::SetSprintAnim_Validate(bool bPressedShift)
//{
//	return true;
//}
//
//void UAdamAnimInstance::SetSprintAnim_Implementation(bool bPressedShift)
//{
//	bIsSprinting = bPressedShift;
//	UE_LOG(PalaceWorld, Error, TEXT("AnimInstance IsSetSprinting = %d"), bIsSprinting);
//}

void UAdamAnimInstance::AnimNotify_TookOutSword()
{
	OnSwordTookOutCheck.Broadcast();
}

void UAdamAnimInstance::AnimNotify_TookOutBow()
{
	OnBowTookOutCheck.Broadcast();
}

void UAdamAnimInstance::AnimNotify_PickArrow()
{
	OnBowPickArrowCheck.Broadcast();
}

void UAdamAnimInstance::AnimNotify_ShootArrow()
{
	OnBowShootArrowCheck.Broadcast();
}

void UAdamAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast(); // 멀티캐스트 델리게이트에 등록된 모든 함수를 호출하는 명령
}

void UAdamAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName UAdamAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	if (FMath::IsWithinInclusive<int32>(Section, 1, 5))
		return FName(*FString::Printf(TEXT("Attack%d"), Section));
	else
		return NAME_None;
	
}

//void UAdamAnimInstance::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME_CONDITION(UAdamAnimInstance, bIsSprinting, COND_SkipOwner);
//	DOREPLIFETIME_CONDITION(UAdamAnimInstance, bIsDead, COND_SkipOwner);
//	DOREPLIFETIME_CONDITION(UAdamAnimInstance, RandDeathAnimIdx, COND_SkipOwner);
//	DOREPLIFETIME_CONDITION(UAdamAnimInstance, bIsChangingWeapon, COND_SkipOwner);
//	DOREPLIFETIME_CONDITION(UAdamAnimInstance, bUsingShield, COND_SkipOwner);
//	DOREPLIFETIME_CONDITION(UAdamAnimInstance, bAimingArrow, COND_SkipOwner);
//}