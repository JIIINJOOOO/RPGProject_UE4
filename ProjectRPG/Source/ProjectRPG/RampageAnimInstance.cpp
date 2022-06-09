// Fill out your copyright notice in the Description page of Project Settings.


#include "RampageAnimInstance.h"

URampageAnimInstance::URampageAnimInstance()
{
	bIsDead = false;
	CurrentPawnSpeed = 0.0f;
	CurrentPawnDir = 0.0f;
	RandAtkAnimIdx = FMath::RandRange(0, 2);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MTG_1(TEXT("/Game/PalaceWorld/Blueprints/Animations/Monster/RampAtkMtg_1.RampAtkMtg_1"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MTG_2(TEXT("/Game/PalaceWorld/Blueprints/Animations/Monster/RampAtkMtg_2.RampAtkMtg_2"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MTG_3(TEXT("/Game/PalaceWorld/Blueprints/Animations/Monster/RampAtkMtg_3.RampAtkMtg_3"));

	if (ATTACK_MTG_1.Succeeded())
	{
		AttackMontage_1 = ATTACK_MTG_1.Object;
	}
	if (ATTACK_MTG_2.Succeeded())
	{
		AttackMontage_2 = ATTACK_MTG_2.Object;
	}
	if (ATTACK_MTG_3.Succeeded())
	{
		AttackMontage_3 = ATTACK_MTG_3.Object;
	}
	
}


void URampageAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn))
		return;

	if (!bIsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		CurrentPawnDir = CalculateDirection(Pawn->GetVelocity(), FRotator(0.0f, Pawn->GetControlRotation().Yaw, 0.0f)); // pawn의 진행방향 구하는 코드
		//UE_LOG(PalaceWorld, Warning, TEXT("Mon Dir:%f"), CurrentPawnDir);
	}
}

void URampageAnimInstance::PlayRandAttackMontage()
{
	UE_LOG(PalaceWorld, Warning, TEXT("Mon anim:%d"), RandAtkAnimIdx);
	switch (RandAtkAnimIdx)
	{
	case 0:
		Montage_Play(AttackMontage_1, 1.0f);
		break;
	case 1:
		Montage_Play(AttackMontage_2, 1.0f);
		break;
	case 2:
		Montage_Play(AttackMontage_3, 1.0f);
		break;
	default:
		break;
	}
}

void URampageAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}
