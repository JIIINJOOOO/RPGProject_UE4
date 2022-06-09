// Fill out your copyright notice in the Description page of Project Settings.


#include "PalaceMonsterSpawner.h"
#include "PalaceRampageMonster.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "Components/SceneComponent.h"


float APalaceMonsterSpawner::SpawnRangeRadius = 800.0f;

// Sets default values
APalaceMonsterSpawner::APalaceMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SpawnInterval = 10.0f;
	PrimaryActorTick.bCanEverTick = true;
	SpawnerComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SPAWNER"));
	RootComponent = SpawnerComponent;
	
}

// Called when the game starts or when spawned
void APalaceMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &APalaceMonsterSpawner::SpawnMonsterAtRandomLocation, SpawnInterval, true, 0.0f);

}

// Called every frame
void APalaceMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APalaceMonsterSpawner::SpawnMonsterAtRandomLocation()
{
	UWorld* World = GetWorld();
	FVector Center = GetActorLocation();
	FVector SpawnLoc;
	FNavLocation SpawnLocFromNav;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FRotator rotator;
//#if ENABLE_DRAW_DEBUG
//	// 범위 디버그 드로잉
//	DrawDebugSphere(World, Center, SpawnRangeRadius, 16, FColor::Green, false, 0.2f);
//#endif
	// 몬스터들이 NavMesh를 통해 갈 수 있는 위치에만 스폰하기 위해서
	if (NavSystem->GetRandomPointInNavigableRadius(Center, SpawnRangeRadius, SpawnLocFromNav))
	{
		SpawnLoc = SpawnLocFromNav.Location;
	}
	World->SpawnActor<APalaceRampageMonster>(APalaceRampageMonster::StaticClass(),SpawnLoc,rotator,SpawnParams);

}

