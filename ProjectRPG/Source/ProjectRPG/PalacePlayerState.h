// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "GameFramework/PlayerState.h"
#include "PalacePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API APalacePlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	APalacePlayerState();

	int32 GetGameScore() const;
	int32 GetCharacterLevel() const;

	void InitPlayerData(/*FString NewPlayerName*/);

protected:
	UPROPERTY(Transient)
	int32 GameScore; // ���� ų�� ����
	
	UPROPERTY(Transient)
	int32 CharacterLevel;
};
