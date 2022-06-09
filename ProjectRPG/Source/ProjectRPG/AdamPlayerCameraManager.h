// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "AdamPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API AAdamPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
	AAdamPlayerCameraManager();
protected:
	float PitchMaxLimit = 0.0f;
	float PitchMinLimit = -70.0f;
	
};
