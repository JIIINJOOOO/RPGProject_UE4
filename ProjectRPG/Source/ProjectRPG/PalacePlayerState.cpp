// Fill out your copyright notice in the Description page of Project Settings.


#include "PalacePlayerState.h"

APalacePlayerState::APalacePlayerState()
{
	CharacterLevel = 3;
	GameScore = 0;
}

int32 APalacePlayerState::GetGameScore() const
{
	return GameScore;
}

int32 APalacePlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
}

void APalacePlayerState::InitPlayerData(/*FString NewPlayerName*/)
{
	UE_LOG(PalaceWorld, Error, TEXT("InitPlayerData Called"));
	SetPlayerName(/*NewPlayerName*/TEXT("Test"));
	CharacterLevel = 5;
	GameScore = 0;
}
