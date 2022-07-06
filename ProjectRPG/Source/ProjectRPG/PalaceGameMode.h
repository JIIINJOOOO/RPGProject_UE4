// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "GameFramework/GameModeBase.h"
#include "PalaceGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API APalaceGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	APalaceGameMode();
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
//	class AAdamObjectPool* GetObjectPool();
//private:
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
//	TSubclassOf<AAdamObjectPool> ObjectPoolClass;
//
//	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
//	AAdamObjectPool* ObjectPool;
};
