// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "Components/ActorComponent.h"
#include "AdamCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelgate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangeDelgate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTRPG_API UAdamCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UAdamCharacterStatComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	void SetNewLevel(int32 NewLevel);
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	float GetAttack();
	float GetHPRatio();

	FOnHPIsZeroDelgate OnHPIsZero;
	FOnHPChangeDelgate OnHPChanged;
private:
	struct FAdamCharacterData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	// 게임 시작때 마다 변경되는 값을 보관하는건 의미가 없으므로 Transient 키워드로 직렬화에서 제외
	UPROPERTY(Transient,VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;
};
