// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\ItemHolderWidget.h"

#include "macros.h"
#include "Blueprint\DragDropOperation.h"
#include "Components\Button.h"
#include "Components\UniformGridPanel.h"
#include "ItemSystem\InventoryComponent.h"
#include "ItemSystem\Item.h"
#include "ItemSystem\ItemHelper.h"
#include "ItemSystem\ItemHolder.h"
#include "UI\ButtonBroadcastSelf.h"
#include "UI\ItemDragDropOperation.h"
#include "UI\ItemWidget.h"

void UItemHolderWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ItemWidget)
	{
		ItemsPanel->ClearChildren();

		for (int i = 0; i < TestItemCount; i++)
		{
			ItemsPanel->AddChild(NewObject<UItemWidget>(this, ItemWidget));
		}
	}
}

FReply UItemHolderWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UItemHolderWidget::OnInventoryUpdated(TScriptInterface<IItemHolder> ChangedItemHolder)
{
	RefreshInventoryUI();
}

int32 UItemHolderWidget::GetMaxPageNumber()
{
	return (ItemsToShow.Num() - 1) / ItemsOnPage;
}

void UItemHolderWidget::RefreshInventoryUI()
{
	ItemsToShow = CurrentItemHolder->GetItems();
	SetupPaginationButtons();

	if (ItemsOnPage * CurrentPage > ItemsToShow.Num())
	{
		CurrentPage = GetMaxPageNumber();
	}

	for (int i = ItemsOnPage * CurrentPage; i < ItemsOnPage; i++)
	{
		if (ItemsToShow.Num() > i)
		{
			ItemWidgets[i]->SetupByItemholder(CurrentItemHolder.GetInterface());
			ItemWidgets[i]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			ItemWidgets[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UItemHolderWidget::OnPaginationClick(UButton* sender)
{
	int oldPage = CurrentPage;
	PaginationButtons.Find(sender, CurrentPage);

	if (oldPage != CurrentPage)
	{
		RefreshInventoryUI();
	}
}


void UItemHolderWidget::SetupPaginationButtons()
{
	for (auto button : PaginationButtons)
	{
		button->SetVisibility(ESlateVisibility::Hidden);
	}

	int maxPages = GetMaxPageNumber();

	if (maxPages > 0)
	{
		for (int i = 0; i <= maxPages; i++)
		{
			if (PaginationButtons.Num() <= i)
			{
				auto button = NewObject<UButtonBroadcastSelf>(this);
				button->OnClickedSelf.AddDynamic(this, &UItemHolderWidget::OnPaginationClick);
				PaginationButtons.Add(button);
				ButtonsPanel->AddChild(button);
			}
			else
			{
				PaginationButtons[i]->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

bool UItemHolderWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                     UDragDropOperation* InOperation)
{
	bool handled = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if (!handled)
	{
		if (UItemDragDropOperation* operation = Cast<UItemDragDropOperation>(InOperation))
		{
			if (!operation->bIsDragFromQuickWidget)
			{
				if (auto payload = Cast<UItem>(InOperation->Payload))
				{
					if (payload->GetHolder() == CurrentItemHolder.GetInterface())
					{
					}
					else
					{
						ItemHelper::AddItemToNewHolder(CurrentItemHolder.GetInterface(),
						                               payload);
					}

					UItemWidget::DragFinished();
					handled = true;
				}
			}
		}
	}

	return handled;
}


void UItemHolderWidget::Setup(IItemHolder* itemHolder)
{
	CurrentPage = 0;

	if (CurrentItemHolder)
	{
		CurrentItemHolder->GetOnInventoryUpdated()->RemoveDynamic(this, &UItemHolderWidget::OnInventoryUpdated);
	}

	CurrentItemHolder = Cast<UObject>(itemHolder);
	RefreshInventoryUI();
	itemHolder->GetOnInventoryUpdated()->AddDynamic(this, &UItemHolderWidget::OnInventoryUpdated);
}


UItemHolderWidget::UItemHolderWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CurrentPage = 0;
	ItemsOnPage = 1;

	Visibility = ESlateVisibility::SelfHitTestInvisible;
}

void UItemHolderWidget::OnItemDropped(UItemWidget* Reciver, UItemDragDropOperation* Payload)
{
	if (Payload->bIsDragFromQuickWidget)
	{
		return;
	}

	UItem* item = Payload->GetItemPayload();
	if (item->GetHolder() != CurrentItemHolder.GetInterface())
	{
		if (Reciver->GetHeldItem())
		{
			ItemHelper::AddItemToNewHolder(item->GetHolder(), Reciver->GetHeldItem());
		}

		ItemHelper::AddItemToNewHolder(CurrentItemHolder.GetInterface(), item);
	}
}

void UItemHolderWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ItemWidgets.Reset();
	ItemsPanel->ClearChildren();

	UItemWidget* item = nullptr;
	CurrentPage = 0;
	for (int i = 0; i < ItemsOnPage; i++)
	{
		item = NewObject<UItemWidget>(this, ItemWidget);
		item->SetItemIndex(i);
		ItemWidgets.Add(item);
		ItemsPanel->AddChild(item);
		item->SetVisibility(ESlateVisibility::Hidden);
		item->OnItemDrop.AddDynamic(this, &UItemHolderWidget::OnItemDropped);
	}

	ButtonsPanel->ClearChildren();
}
