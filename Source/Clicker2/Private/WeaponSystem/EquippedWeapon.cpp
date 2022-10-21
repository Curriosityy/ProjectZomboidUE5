// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/EquippedWeapon.h"

#include "GameMode/Clicker2GameMode.h"
#include "ItemSystem/Item.h"
#include "WeaponSystem/WeaponActor.h"
#include "WeaponSystem/WeaponAttackComponent.h"
#include "WeaponSystem/WeaponItemData.h"

void UEquippedWeapon::Initialize(EItemType itemType, FName Socket, USkeletalMeshComponent* playerMesh, UEquippedWeapon* secondHand)
{
	Super::Initialize(itemType);
	SocketName = Socket;
	PlayerSkeletalMesh = playerMesh;
	SecondHand = secondHand;
}



bool UEquippedWeapon::AddItem(IItemHolder* previousOwner, UItem* item)
{
	if(CanAddItem(item))
	{
		bool bCanHeld = true;
		auto weapon = static_cast<UWeaponItemData*>(item->GetItemData());
		
		if(weapon)//Can be 2Hand
		{
			if(weapon->IsTwoHanded())
			{
				bCanHeld=SecondHand->Super::AddItem(nullptr, item);
			}
		}

		if(bCanHeld)
		{
			Super::AddItem(previousOwner, item);

			if(weapon && weapon->GetWeaponAttackComponent())
			{
				if(AttackComponent)
				{
					AttackComponent->DestroyComponent();
				}
				
				AttackComponent = NewObject<UWeaponAttackComponent>(PlayerSkeletalMesh->GetAttachmentRootActor(), weapon->GetWeaponAttackComponent());
				AttackComponent->RegisterComponent();
			}
			
			SpawnedObject = GetWorld()->SpawnActor<AWeaponActor>();
			FAttachmentTransformRules attachementRule = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
			SpawnedObject->SkeletalMeshComponent->SetSkeletalMesh(static_cast<USkeletalMesh*>(item->GetItemData()->GetItemInWorld()));
			SpawnedObject->AttachToComponent(PlayerSkeletalMesh, attachementRule, SocketName);
		}
	
		return bCanHeld;
	}
	
	return false; 
}

bool UEquippedWeapon::RemoveItem(UItem* item)
{
	
	if(auto weaponID = static_cast<UWeaponItemData*>(item->GetItemData()))
	{
		if(weaponID->IsTwoHanded())
		{
			SecondHand->Super::RemoveItem(item);
		}
	}

	if(AttackComponent)
	{
		AttackComponent->DestroyComponent();
	}
	
	GetWorld()->DestroyActor(SpawnedObject);
	
	return Super::RemoveItem(item);
}
