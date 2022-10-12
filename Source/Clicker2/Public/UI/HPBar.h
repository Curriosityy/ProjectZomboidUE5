// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPBar.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CLICKER2_API UHPBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealthComponent(class UHPComponent* healthComp);

protected:
	TWeakObjectPtr<UHPComponent> healthComponent;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* ProgressBar;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* CurrentHp;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* MaxHp;

	virtual void NativeTick(const FGeometry& myGeometry, float inDeltaTime) override;
};
