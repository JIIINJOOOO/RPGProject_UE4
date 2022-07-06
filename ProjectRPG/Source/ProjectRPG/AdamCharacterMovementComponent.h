// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AdamCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API UAdamCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()
	virtual float GetMaxSpeed() const override;
};
