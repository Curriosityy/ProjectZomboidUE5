// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\DropItemOnGroundUserWidget.h"
#include "macros.h"
#include "Blueprint\DragDropOperation.h"
#include "ItemSystem\Item.h"
#include "ItemSystem\ItemHelper.h"
#include "ItemSystem\SearchForPickupColliderComponent.h"
#include "Player\Clicker2Character.h"
#include "UI\ItemDragDropOperation.h"
#include "UI\ItemWidget.h"


bool UDropItemOnGroundUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                               UDragDropOperation* InOperation)
{
	bool handled = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if (!handled)
	{
		if (UItemDragDropOperation* operation = Cast<UItemDragDropOperation>(InOperation))
		{
			if (!operation->bIsDragFromQuickWidget)
			{
				if (UItem* Payload = Cast<UItem>(InOperation->Payload))
				{
					if (Payload->GetHolder() != SearchItemComp)
					{
						ItemHelper::AddItemToNewHolder(SearchItemComp, Payload);
					}

					UItemWidget::DragFinished();
					handled = true;
				}
			}
		}
	}

	return handled;
}

void UDropItemOnGroundUserWidget::Setup(AClicker2Character* Character)
{
	CurrentCharacter = Character;
	SearchItemComp = Character->GetSearchItemComponent();
}
