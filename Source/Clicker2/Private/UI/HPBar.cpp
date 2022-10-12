// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HPBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Player/HPComponent.h"

void UHPBar::SetHealthComponent(UHPComponent* healthComp)
{
	this->healthComponent = healthComp;
}

void UHPBar::NativeTick(const FGeometry& myGeometry, float inDeltaTime)
{
	Super::NativeTick(myGeometry, inDeltaTime);

	if (healthComponent.IsValid())
	{
		ProgressBar->SetPercent((healthComponent->GetCurrentHp() * 1.f) / healthComponent->GetMaxHp());
		MaxHp->SetText(FText::AsNumber(healthComponent->GetMaxHp()));
		CurrentHp->SetText(FText::AsNumber(healthComponent->GetCurrentHp()));
	}
}
