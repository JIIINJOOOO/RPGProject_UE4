// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "PalaceGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FAdamCharacterData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FAdamCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
};

/**
 * 
 */


UCLASS()
class PROJECTRPG_API UPalaceGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPalaceGameInstance();

	virtual void Init() override;
	FAdamCharacterData* GetAdamCharacterData(int32 Level);
public:
	class AAdamObjectPool* GetObjectPool();
private:
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	AAdamObjectPool* ObjectPool;

	UPROPERTY()
	class UDataTable* AdamCharacterTable;
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AAdamObjectPool> ObjectPoolClass;*/
};
