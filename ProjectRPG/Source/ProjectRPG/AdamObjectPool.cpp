// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamObjectPool.h"
#include "AdamArrow.h"

// Sets default values
AAdamObjectPool::AAdamObjectPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAdamObjectPool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAdamObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AAdamArrow* AAdamObjectPool::GetPooledObject()
{
	if (Pool.Num() == 0)
		Expand();
	return Pool.Pop();
}

void AAdamObjectPool::Expand()
{
	for (int i = 0; i < ExpandSize; ++i)
	{
		AAdamArrow* PoolableActor = GetWorld()->SpawnActor<AAdamArrow>(AAdamArrow::StaticClass(), FVector().ZeroVector, FRotator().ZeroRotator);
		PoolableActor->SetActive(false);
		PoolableActor->SetObjectPool(this);
		Pool.Push(PoolableActor);
	}
	PoolSize += ExpandSize;
}

void AAdamObjectPool::ReturnObject(AAdamArrow* ReturnObject)
{
	Pool.Push(ReturnObject);
}

