// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\ItemWidget.h"

#include "macros.h"
#include "Blueprint\DragDropOperation.h"
#include "Components\Image.h"
#include "Components\TextBlock.h"
#include "ItemSystem\Item.h"
#include "ItemSystem\ItemHelper.h"
#include "ItemSystem\ItemHolder.h"
#include "ItemSystem\ItemDatas\ItemData.h"
#include "Player\Clicker2Character.h"
#include "UI\GameHUD.h"
#include "UI\ItemDragDropOperation.h"

TObjectPtr<UItem> UItemWidget::GetHeldItem() const
{
	return HeldItem;
}

void UItemWidget::SetupByItemholder(IItemHolder* itemHolder)
{
	UItem* item = nullptr;

	if (itemHolder)
	{
		TArray<UItem*> items = itemHolder->GetItems();

		if (items.Num() > Index)
		{
			item = items[Index];
		}
	}

	if (item == nullptr)
	{
		HeldItem = nullptr;
		SetValues(nullptr, 0);
	}
	else
	{
		HeldItem = item;
		SetValues(item->GetItemData()->GetItemThumbnail());
	}
}

void UItemWidget::SetItem(UItem* item)
{
	if (item == nullptr)
	{
		HeldItem = nullptr;
		SetIcon(nullptr);
	}
	else
	{
		HeldItem = item;
		SetIcon(item->GetItemData()->GetItemThumbnail());
	}
}

void UItemWidget::SetupByItemholder(TScriptInterface<IItemHolder> itemHolderScriptInterface)
{
	SetupByItemholder(itemHolderScriptInterface.GetInterface());
}

void UItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UItemWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (EmptySlot)
	{
		ItemIcon->SetBrushFromTexture(EmptySlot, false);
	}
}

void UItemWidget::SetIcon(UTexture2D* texture)
{
	if (texture == nullptr)
	{
		texture = EmptySlot;
	}

	ItemIcon->SetBrushFromTexture(texture, false);
}

void UItemWidget::SetCount(int count, bool ForceToShow = false)
{
	if (count <= 1 && !ForceToShow)
	{
		CountText->SetText(FText::FromString(""));
	}
	else
	{
		CountText->SetText(FText::AsNumber(count));
	}
}

void UItemWidget::SetItemIndex(int index)
{
	this->Index = index;
}

void UItemWidget::SetValues(UTexture2D* texture, int count)
{
	SetIcon(texture);
	SetCount(count);
}

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (HeldItem)
	{
		if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			HeldItem->Use(GetOwningPlayer()->GetPawn<AClicker2Character>());
		}
		else if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			if (GetOwningPlayer()->IsInputKeyDown(EKeys::LeftShift) || GetOwningPlayer()->IsInputKeyDown(
				EKeys::RightShift))
			{
				Cast<AGameHUD>(GetOwningPlayer()->GetHUD())->MoveItemBetweenInventoryAndScavengeItemHolders(HeldItem);
			}
			else
			{
				reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
				reply.Handled();
			}
		}
	}

	return reply;
}

void UItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                       UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UItemDragDropOperation* outOperation = NewObject<UItemDragDropOperation>(this, DragNDropOperation);
	OutOperation = outOperation;


	outOperation->Payload = HeldItem;
	auto image = NewObject<UImage>();
	image->SetVisibility(ESlateVisibility::HitTestInvisible);
	image->SetBrush(ItemIcon->Brush);
	outOperation->DefaultDragVisual = image;
	sIsDragged = true;
	OnStartDrag.Broadcast(this, outOperation);
}

void UItemWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	DragFinished();
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

bool UItemWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                               UDragDropOperation* InOperation)
{
	bool handled = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if (!handled)
	{
		if (UItemDragDropOperation* operation = Cast<UItemDragDropOperation>(InOperation))
		{
			if (auto payload = static_cast<UItem*>(InOperation->Payload))
			{
				OnItemDrop.Broadcast(this, operation);
			}
		}

		DragFinished();
	}

	return handled;
}

void UItemWidget::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);

	if (InVisibility == ESlateVisibility::Hidden)
	{
		HeldItem = nullptr;
	}
}

void UItemWidget::DragFinished()
{
	sIsDragged = false;
}
