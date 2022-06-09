// Fill out your copyright notice in the Description page of Project Settings.


#include "PalaceGameMode.h"
#include "AdamCharacter.h"
#include "AdamPlayerController.h"
//#include "AdamObjectPool.h"

APalaceGameMode::APalaceGameMode() 
{
	DefaultPawnClass = AAdamCharacter::StaticClass();
	PlayerControllerClass = AAdamPlayerController::StaticClass();
}


//AAdamObjectPool* APalaceGameMode::GetObjectPool()
//{
//	if (!ObjectPool)
//		ObjectPool = Cast<AAdamObjectPool>(GetWorld()->SpawnActor(AAdamObjectPool::StaticClass()));
//	return ObjectPool;
//}
