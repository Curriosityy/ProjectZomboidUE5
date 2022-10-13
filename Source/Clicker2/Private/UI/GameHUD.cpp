// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Player/Clicker2Character.h"
#include "UI/InventoryUserWidget.h"
#include "UI/ItemWidget.h"
#include "UI/ScavengingUserWidget.h"

AGameHUD::AGameHUD()
{
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
	UItemWidget::sIsDragged = false;
}

void AGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AGameHUD::OpenInventoryWindow(AClicker2Character* characterToOpenInventory)
{
	if (Inventory == nullptr)
	{
		Inventory = CreateWidget<UInventoryUserWidget>(GetWorld(), InventoryWidget);
		
		if (Inventory)
		{
			MouseBlockers.Add(Inventory);
			Inventory->AddToViewport();
			Inventory->Show(characterToOpenInventory);
		}
	}
	else
	{
		Inventory->Show(characterToOpenInventory);
	}
}

void AGameHUD::OpenScavengeWindow(AClicker2Character* characterToOpenInventory)
{
	if (Scavenge == nullptr)
	{
		Scavenge = CreateWidget<UScavengingUserWidget>(GetWorld(), ScavengeWidget);
		
		if (Scavenge)
		{
			MouseBlockers.Add(Scavenge);
			Scavenge->AddToViewport();
			Scavenge->Show(characterToOpenInventory->GetSearchItemComponent());
		}
	}
	else
	{
		Scavenge->Show(characterToOpenInventory->GetSearchItemComponent());
	}
}

bool AGameHUD::IsMouseOverBlockUI()
{
	bool mouseOver = false;
	
	for (auto Element : MouseBlockers)
	{
		mouseOver |= Element->IsMouseOver();
	}

	mouseOver |= UItemWidget::IsDragged();
	
	return mouseOver;
}
