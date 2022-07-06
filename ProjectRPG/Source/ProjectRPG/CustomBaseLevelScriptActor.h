// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "Engine/LevelScriptActor.h"
#include "CustomBaseLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API ACustomBaseLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
};
