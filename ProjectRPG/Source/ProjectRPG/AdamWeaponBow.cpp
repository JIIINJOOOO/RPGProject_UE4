// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamWeaponBow.h"

// Sets default values
AAdamWeaponBow::AAdamWeaponBow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Weapon_BowMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON_BOW")); // È° ½ºÄÌ·¹Å» ¸Þ½¬
	RootComponent = Weapon_BowMesh;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BOW(TEXT("/Game/PalaceWorld/Resources/Adam_Adventurer/Meshes/Character/Bow/SK_Bow.SK_Bow"));
	if (SK_BOW.Succeeded())
	{
		Weapon_BowMesh->SetSkeletalMesh(SK_BOW.Object);
	}
	Weapon_BowMesh->SetCollisionProfileName(TEXT("NoCollision"));
	Weapon_BowMesh->SetVisibility(false);
}

// Called when the game starts or when spawned
void AAdamWeaponBow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAdamWeaponBow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

