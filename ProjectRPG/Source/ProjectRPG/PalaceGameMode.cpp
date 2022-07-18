// Fill out your copyright notice in the Description page of Project Settings.


#include "PalaceGameMode.h"
#include "AdamCharacter.h"
#include "AdamPlayerController.h"
#include "PalacePlayerState.h"
//#include "AdamObjectPool.h"

APalaceGameMode::APalaceGameMode() 
{
	DefaultPawnClass = AAdamCharacter::StaticClass();
	PlayerControllerClass = AAdamPlayerController::StaticClass();
	PlayerStateClass = APalacePlayerState::StaticClass();

}


//AAdamObjectPool* APalaceGameMode::GetObjectPool()
//{
//	if (!ObjectPool)
//		ObjectPool = Cast<AAdamObjectPool>(GetWorld()->SpawnActor(AAdamObjectPool::StaticClass()));
//	return ObjectPool;
//}

void APalaceGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	auto PalacePlayerState = Cast<APalacePlayerState>(NewPlayer->PlayerState);
	if (nullptr != PalacePlayerState)
	{
		PalacePlayerState->InitPlayerData();
	}

}
