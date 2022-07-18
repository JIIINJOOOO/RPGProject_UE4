// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamCharacterStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PalaceGameInstance.h"
#include "Net/UnrealNetwork.h"

// Sets default values
UAdamCharacterStatComponent::UAdamCharacterStatComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;

}

// Called when the game starts or when spawned
void UAdamCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAdamCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UAdamCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto AdamGameInstance = Cast<UPalaceGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr != AdamGameInstance)
	{
		CurrentStatData = AdamGameInstance->GetAdamCharacterData(NewLevel);
		if (nullptr != CurrentStatData)
		{
			Level = NewLevel;
			SetHP(CurrentStatData->MaxHP);
			CurrentHP = CurrentStatData->MaxHP;
		}
		else
		{
			UE_LOG(PalaceWorld,Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
		}
	}
}

void UAdamCharacterStatComponent::SetDamage_Implementation(float NewDamage)
{
	if (nullptr != CurrentStatData)
	{
		SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
		if (CurrentHP <= 0.0f)
		{
			OnHPIsZero.Broadcast();
		}
	}
}

void UAdamCharacterStatComponent::SetHP_Implementation(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

float UAdamCharacterStatComponent::GetAttack()
{
	if(nullptr == CurrentStatData)
		return 0.0f;
	return CurrentStatData->Attack;
}

float UAdamCharacterStatComponent::GetHPRatio()
{
	if (nullptr == CurrentStatData)
		return 0.0f;
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
	
}



void UAdamCharacterStatComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 모두에게
	DOREPLIFETIME(UAdamCharacterStatComponent, CurrentHP);


}