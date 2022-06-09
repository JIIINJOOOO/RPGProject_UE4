// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "Blueprint/UserWidget.h"
#include "AdamCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API UAdamCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void BindCharacterStat(class UAdamCharacterStatComponent* NewCharacterStat);
protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();
private:
	TWeakObjectPtr<class UAdamCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;
};
