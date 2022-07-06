// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamCharacterMovementComponent.h"
#include "AdamCharacter.h"

UAdamCharacterMovementComponent::UAdamCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

float UAdamCharacterMovementComponent::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	const AAdamCharacter* AdamCharacterOwner = Cast<AAdamCharacter>(PawnOwner);
	if (AdamCharacterOwner)
	{
		if (AdamCharacterOwner->IsSprinting())
		{
			MaxSpeed *= AdamCharacterOwner->GetSprintingSpeedModifier();
		}
	}

	return MaxSpeed;
}
