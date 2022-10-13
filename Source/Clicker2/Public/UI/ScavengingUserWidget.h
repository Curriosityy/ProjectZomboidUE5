// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameWindowUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "ScavengingUserWidget.generated.h"

class IItemHolder;
class USearchForPickupColliderComponent;
class UItemHolderWidget;
/**
 * 
 */
UCLASS()
class CLICKER2_API UScavengingUserWidget : public UMainGameWindowUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UItemHolderWidget> ItemHolderWidget;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UPanelWidget> ButtonsPanel;

	UPROPERTY(Transient, NonTransactional)
	TArray<TObjectPtr<UButton>> Buttons;

	UPROPERTY(Transient, NonTransactional)
	USearchForPickupColliderComponent* CurrentPickupComponent;

	//Contain IItemHolders
	UPROPERTY(Transient, NonTransactional)
	TArray<TScriptInterface<IItemHolder>> ItemHolders;
	
	int CurrentWidgetIndex = 0;

	UFUNCTION()
	void SwitchScavengingTab(UButton* Sender);
	void RebuildItemHoldersList();

	UFUNCTION()
	void OnOverlappedContainersChanged(USearchForPickupColliderComponent* sender);
	
	void RefreshButtons();

	virtual void Show() override;

	virtual void NativeConstruct() override;
public:

	void Show(USearchForPickupColliderComponent* pickupComponent);
	void RefreshItemHolderWidget();
};
