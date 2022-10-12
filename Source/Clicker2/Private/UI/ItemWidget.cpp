// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemWidget.h"

#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemSystem/Item.h"
#include "ItemSystem/ItemHolder.h"
#include "ItemSystem/ItemDatas/ItemData.h"
#include "Player/Clicker2Character.h"

void UItemWidget::SetItem(IItemHolder* itemHolder)
{
	UItem* item = nullptr;

	if (itemHolder)
	{
		auto items = itemHolder->GetItems();

		if (items.Num() > Index)
		{
			item = itemHolder->GetItems()[Index];
		}
	}

	ItemHolder = itemHolder;

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

void UItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UItemWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(EmptySlot)
	{
		ItemIcon->SetBrushFromTexture(EmptySlot,false);
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

void UItemWidget::SetCount(int count)
{
	if (count <= 1)
	{
		CountText->SetText(FText::FromString(""));
	}
	else
	{
		CountText->SetText(FText::AsNumber(count));
	}
}

void UItemWidget::Init(int index)
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
			reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
			reply.Handled();
		}
	}

	return reply;
}

void UItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                       UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (!OutOperation)
	{
		OutOperation = NewObject<UDragDropOperation>(this);
	}

	OutOperation->Payload = HeldItem;
	auto image = NewObject<UImage>();
	image->SetVisibility(ESlateVisibility::HitTestInvisible);
	image->SetBrush(ItemIcon->Brush);
	OutOperation->DefaultDragVisual = image;
	sIsDragged = true;
}

void UItemWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	sIsDragged = false;
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}


bool UItemWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                               UDragDropOperation* InOperation)
{
	bool handled = false;
	if (!Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation))
	{
		if (auto sender = static_cast<UItemWidget*>(InOperation->GetOuter()))
		{
			if (sender->ItemHolder == ItemHolder)
			{
				//ItemHolder->Move(sender->Index, Index);
				handled = true;
			}
			else
			{
			}
		}
	}
	
	sIsDragged = false;
	return handled;
}
