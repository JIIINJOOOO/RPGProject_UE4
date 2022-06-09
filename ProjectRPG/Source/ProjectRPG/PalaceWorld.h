// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
DECLARE_LOG_CATEGORY_EXTERN(PalaceWorld, Log, All);

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	E_SWORDSHIELD UMETA(DisplayName = "SwordShield"),
	E_BOW UMETA(DisplayName = "Bow")
};
/**
 * 
 */
//class PROJECTRPG_API PalaceWorld
//{
//public:
//	PalaceWorld();
//	~PalaceWorld();
//};
