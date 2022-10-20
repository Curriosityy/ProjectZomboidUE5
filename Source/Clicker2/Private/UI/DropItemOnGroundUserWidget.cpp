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
		if (UItemWidget* Payload = static_cast<UItemWidget*>(InOperation->Payload))
		{
			if(Payload->GetItemHolder() && Payload->GetHeldItem())
			{
				if(Payload->GetItemHolder() != SearchItemComp)
				{
					SearchItemComp->AddItem(Payload->GetItemHolder(),Payload->GetHeldItem());
				}
			}
			
			Payload->DragFinished();
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
