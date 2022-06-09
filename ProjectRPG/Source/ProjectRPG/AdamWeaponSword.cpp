// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamWeaponSword.h"

// Sets default values
AAdamWeaponSword::AAdamWeaponSword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon_SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON_SWORD")); // Ä® ½ºÅÂÆ½ ¸Þ½¬
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SWORD(TEXT("/Game/PalaceWorld/Resources/Adam_Adventurer/Meshes/SM_Adam_Sword.SM_Adam_Sword"));
	if (SM_SWORD.Succeeded())
	{
		Weapon_SwordMesh->SetStaticMesh(SM_SWORD.Object);
	}
	Weapon_SwordMesh->SetCollisionProfileName(TEXT("NoCollision"));


}

// Called when the game starts or when spawned
void AAdamWeaponSword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAdamWeaponSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

