// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "GameFramework/Actor.h"
#include "PalaceMonsterSpawner.generated.h"

UCLASS()
class PROJECTRPG_API APalaceMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APalaceMonsterSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USceneComponent* SpawnerComponent;
public:
	void SpawnMonsterAtRandomLocation();
private:
	FTimerHandle SpawnTimerHandle;
	float SpawnInterval;
	
	static float SpawnRangeRadius; // ���� ���� 
	class UNavigationSystemV1* NavSystem;
};
