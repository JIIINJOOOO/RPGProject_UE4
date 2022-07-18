// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamCharacterWidget.h"
#include "AdamCharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UAdamCharacterWidget::BindCharacterStat(class UAdamCharacterStatComponent* NewCharacterStat)
{
	if (nullptr == NewCharacterStat)
		return;
	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UAdamCharacterWidget::UpdateHPWidget);

}

void UAdamCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	if (nullptr != HPProgressBar)
	{
		UpdateHPWidget();
	}
}

void UAdamCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		//UE_LOG(PalaceWorld, Warning, TEXT("UpdateHPWidget Called"));
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}
