// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "GameFramework/Actor.h"
#include "AdamObjectPool.generated.h"

UCLASS()
class PROJECTRPG_API AAdamObjectPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdamObjectPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	class AAdamArrow* GetPooledObject(); // 오브젝트 풀에서 관리하는 오브젝트를 하나 반환하는 함수
	void Expand(); // 오브젝트 풀에 반환 가능한 객체가 더 이상 없을 경우 오브젝트 풀을 확장(객체 늘림)하는 함수
	void ReturnObject(class AAdamArrow* ReturnObject); // 오브젝트 풀에 반환된 객체를 오브젝트 풀에 추가하는 함수
public:
	TSubclassOf<class AAdamArrow> PooledObjectSubClass; // 관리할 오브젝트 클래스
	int32 PoolSize = 0; // 오브젝트 풀 기본 크기
	int32 ExpandSize = 10; // 오브젝트 풀 확장 크기
private:
	TArray<class AAdamArrow*> Pool; // 오브젝트 풀

};
