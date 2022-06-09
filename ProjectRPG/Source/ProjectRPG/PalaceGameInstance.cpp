// Fill out your copyright notice in the Description page of Project Settings.


#include "PalaceGameInstance.h"
#include "AdamObjectPool.h"

UPalaceGameInstance::UPalaceGameInstance()
{
	FString CharacterDataPath = TEXT("/Game/PalaceWorld/Blueprints/GameData/AdamCharacterData.AdamCharacterData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ADAMCHAR(*CharacterDataPath);
	if (DT_ADAMCHAR.Succeeded())
	{
		AdamCharacterTable = DT_ADAMCHAR.Object;
		if (AdamCharacterTable->GetRowMap().Num() > 0)
			return;
	}
}

void UPalaceGameInstance::Init()
{
	Super::Init();
	UE_LOG(PalaceWorld, Warning, TEXT("MaxHP of Level 1 AdamCharacter : %d"), GetAdamCharacterData(1)->MaxHP);
}

FAdamCharacterData* UPalaceGameInstance::GetAdamCharacterData(int32 Level)
{
	return AdamCharacterTable->FindRow<FAdamCharacterData>(*FString::FromInt(Level),TEXT(""));
}

AAdamObjectPool* UPalaceGameInstance::GetObjectPool()
{
	if (!ObjectPool)
		ObjectPool = Cast<AAdamObjectPool>(GetWorld()->SpawnActor(AAdamObjectPool::StaticClass()));
	return ObjectPool;
}

