// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamWeaponShield.h"

// Sets default values
AAdamWeaponShield::AAdamWeaponShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Weapon_ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON_SHIELD")); // Ä® ½ºÅÂÆ½ ¸Þ½¬
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SHIELD(TEXT("/Game/PalaceWorld/Resources/Adam_Adventurer/Meshes/SM_Adam_Shield.SM_Adam_Shield"));
	if (SM_SHIELD.Succeeded())
	{
		Weapon_ShieldMesh->SetStaticMesh(SM_SHIELD.Object);
	}
	Weapon_ShieldMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AAdamWeaponShield::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAdamWeaponShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

