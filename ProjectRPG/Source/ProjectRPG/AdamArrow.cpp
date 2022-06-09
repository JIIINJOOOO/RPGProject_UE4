// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamArrow.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AdamObjectPool.h"
#include "Kismet/GameplayStatics.h"

float AAdamArrow::DmgByPlayerLv = 0.0f;

// Sets default values
AAdamArrow::AAdamArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Bow_ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ARROW")); // 칼 스태틱 메쉬
	ArrowColBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ArrowColBox"));
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_ARROW(TEXT("/Game/PalaceWorld/Resources/Adam_Adventurer/Meshes/SM_Adam_Arrow.SM_Adam_Arrow"));
	if (SM_ARROW.Succeeded())
	{
		Bow_ArrowMesh->SetStaticMesh(SM_ARROW.Object);
	}
	
	Bow_ArrowMesh->SetCollisionProfileName(TEXT("NoCollision"));
	Bow_ArrowMesh->SetupAttachment(ArrowColBox);
	//SetRootComponent(Bow_ArrowMesh);
	// 충돌 프로파일 적용
	ArrowColBox->SetCollisionProfileName(TEXT("PlayerArrow"));
	ArrowColBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));
	//ArrowColBox->SetupAttachment(Bow_ArrowMesh);
	RootComponent = ArrowColBox;

	Movement->UpdatedComponent = ArrowColBox;
	Movement->InitialSpeed = 1200.f; // 2000.f
	Movement->MaxSpeed = 1200.f;
	Movement->bRotationFollowsVelocity = true;
	//Movement->bShouldBounce = true;
	//Movement->Bounciness = 0.3f;
	//Movement->bInitialVelocityInLocalSpace = true;
	Movement->ProjectileGravityScale = 0.5f;
	Movement->bAutoActivate = false;

	returnInterval = 3.0f;
}

// Called when the game starts or when spawned
void AAdamArrow::BeginPlay()
{
	Super::BeginPlay();
	// 델리게이트에 생성한 함수 등록
	ArrowColBox->OnComponentHit.AddDynamic(this, &AAdamArrow::OnHit);

}

// Called every frame
void AAdamArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAdamArrow::ShootInDirection(const FVector& ShootDirection)
{
	Movement->Velocity = ShootDirection * Movement->InitialSpeed;
}

void AAdamArrow::ReturnSelf()
{
	if (m_ObjectPool == nullptr)
	{
		UE_LOG(PalaceWorld, Warning, TEXT("m_ObjectPool is NULL"));
		return;
	}
	SetActive(false);
	m_ObjectPool->ReturnObject(this);
	Bow_ArrowMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f)); // 메쉬 방향
}

void AAdamArrow::SetActive(bool bIsActive)
{
	m_bIsActive = bIsActive;
	SetActorHiddenInGame(!m_bIsActive);
	SetActorEnableCollision(m_bIsActive);
}

void AAdamArrow::OnActivated(const FVector& ShootDir)
{
	ShootInDirection(ShootDir);
	Bow_ArrowMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f)); // 메쉬 방향 set
	Movement->SetUpdatedComponent(ArrowColBox);
	Movement->SetComponentTickEnabled(true);
	Movement->UpdateComponentVelocity();
	Movement->Activate();
}



void AAdamArrow::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(PalaceWorld, Warning, TEXT("Hit Actor Name : %s"), *Hit.Actor->GetName());

	SetActorEnableCollision(false);
	GetWorldTimerManager().SetTimer(ArrowTimerHandle, this, &AAdamArrow::ReturnSelf, 1.0f, false, returnInterval);
	if (Hit.Actor.IsValid())
	{
		FDamageEvent DamageEvent;
		// 여기서 OtherActor는 ProjectileArrow와 충돌한 객체, 즉 몬스터 객체이다
		float fDamage = OtherActor->TakeDamage(DmgByPlayerLv/*나중에 캐릭터 스탯에서 받아오는 처리 필요*/, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
	}
}


