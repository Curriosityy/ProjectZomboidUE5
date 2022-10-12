// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameWindowUserWidget.h"
#include "InventoryUserWidget.generated.h"

class AClicker2Character;
class UItemHolderWidget;
class UPlayerStatsUserWidget;
class UEquipmentUserWidget;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class CLICKER2_API UInventoryUserWidget : public UMainGameWindowUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ButtonEquipment;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ButtonPlayerStats;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ButtonItemHolder;

	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UEquipmentUserWidget> Equipment;

	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UPlayerStatsUserWidget> PlayerStats;
	
	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UItemHolderWidget> ItemHolder;

public:
	virtual void Show(AClicker2Character* playerToShow);
	
	virtual void Hide() override;

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void ShowEqTab();
	UFUNCTION()
	void ShowStatTab();
	UFUNCTION()
	void ShowItemsTab();

protected:
	virtual void Show() override;
};
