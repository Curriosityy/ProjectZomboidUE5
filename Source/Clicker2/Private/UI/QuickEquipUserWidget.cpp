// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\QuickEquipUserWidget.h"

#include "Blueprint\DragDropOperation.h"
#include "Components\HorizontalBox.h"
#include "ItemSystem\BasicItemContainer.h"
#include "ItemSystem\InventoryComponent.h"
#include "ItemSystem\ItemHelper.h"
#include "Player\Clicker2Character.h"
#include "UI\ItemDragDropOperation.h"
#include "UI\ItemWidget.h"


void UQuickEquipUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (QuickEquipBox && ItemWidget)
	{
		QuickEquipBox->ClearChildren();

		for (int i = 0; i < QuickEquipCount; i++)
		{
			QuickEquipBox->AddChild(NewObject<UItemWidget>(this, ItemWidget));
		}
	}
}

UItemWidget* UQuickEquipUserWidget::FindItemWidget(UItem* Item)
{
	UItemWidget* widget = nullptr;

	for (int i = 0; i < QuickEquipItemWidgets.Num(); i++)
	{
		if (QuickEquipItemWidgets[i]->GetHeldItem() == Item)
		{
			widget = QuickEquipItemWidgets[i];
			break;
		}
	}

	return widget;
}

void UQuickEquipUserWidget::OnQuickItemItemHolderChanged(UItem* Item)
{
	if (!ItemHelper::IsInventoryItemHolder(Owner, Item->GetHolder()))
	{
		RemoveQuickItem(Item);
	}
}

void UQuickEquipUserWidget::RemoveQuickItem(UItem* Item)
{
	FindItemWidget(Item)->SetItem(nullptr);
	Item->OnItemHolderChanged.RemoveDynamic(this, &UQuickEquipUserWidget::OnQuickItemItemHolderChanged);
}

void UQuickEquipUserWidget::OnItemDroped(UItemWidget* Reciver, UItemDragDropOperation* Payload)
{
	bool isReadyToAdd = true;

	UItem* item = Payload->GetItemPayload();

	if (!ItemHelper::IsInventoryItemHolder(Owner, item->GetHolder()))
	{
		isReadyToAdd = ItemHelper::AddItemToNewHolder(Owner->GetInventoryComponent()->GetHeldItems(), item);
	}

	if (isReadyToAdd)
	{
		if (FindItemWidget(item))
		{
			RemoveQuickItem(Payload);
		}

		if (Reciver->GetHeldItem())
		{
			RemoveQuickItem(Reciver->GetHeldItem());
		}

		Reciver->SetItem(item);
		item->OnItemHolderChanged.AddDynamic(this, &UQuickEquipUserWidget::OnQuickItemItemHolderChanged);
	}
}

void UQuickEquipUserWidget::RemoveQuickItem(UDragDropOperation* Operation)
{
	if (UItem* payload = Cast<UItem>(Operation->Payload))
	{
		RemoveQuickItem(payload);
	}
}

void UQuickEquipUserWidget::OnStartDrag(UItemWidget* Sender, UItemDragDropOperation* Payload)
{
	Payload->bIsDragFromQuickWidget = true;
	Payload->OnDragCancelled.AddDynamic(this, &UQuickEquipUserWidget::RemoveQuickItem);
}

void UQuickEquipUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Owner = GetOwningPlayer()->GetPawn<AClicker2Character>();

	if (QuickEquipBox && ItemWidget)
	{
		QuickEquipBox->ClearChildren();

		for (int i = 0; i < QuickEquipCount; i++)
		{
			UItemWidget* item = NewObject<UItemWidget>(this, ItemWidget);
			QuickEquipBox->AddChild(item);
			QuickEquipItemWidgets.Add(item);
			item->SetCount(i + 1, true);
			item->SetVisibility(ESlateVisibility::Visible);
			item->OnItemDrop.AddDynamic(this, &UQuickEquipUserWidget::OnItemDroped);
			item->OnStartDrag.AddDynamic(this, &UQuickEquipUserWidget::OnStartDrag);
		}
	}
}

void UQuickEquipUserWidget::QuickUse(int id, AClicker2Character* character)
{
	TObjectPtr<UItem> item = QuickEquipItemWidgets[id]->GetHeldItem();

	if (item)
	{
		item->Use(character);
	}
}
