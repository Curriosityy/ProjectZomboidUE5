// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DropItemOnGroundUserWidget.h"
#include "Player/Clicker2Character.h"
#include "macros.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemSystem/SearchForPickupColliderComponent.h"
#include "UI/ItemWidget.h"


bool UDropItemOnGroundUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                               UDragDropOperation* InOperation)
{
	bool handled = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if(!handled)
	{
		if (auto sender = static_cast<UItemWidget*>(InOperation->Payload))
		{
			if(sender->GetItemHolder() && sender->GetHeldItem())
			{
				if(sender->GetItemHolder() != SearchItemComp)
				{
					SearchItemComp->AddItem(sender->GetItemHolder(),sender->GetHeldItem());
				}
			}
			
			sender->DragFinished();
			handled=true;
		}
	}
	
	return handled;
}

void UDropItemOnGroundUserWidget::Setup(AClicker2Character* Character)
{
	CurrentCharacter = Character;
	SearchItemComp = Character->GetSearchItemComponent();
}
