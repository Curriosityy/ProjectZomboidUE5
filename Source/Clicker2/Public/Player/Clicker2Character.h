// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Clicker2Character.generated.h"

class UGunItemdata;
class USearchForPickupColliderComponent;
class UPlayerStatsComponent;
class UItem;
class USpringArmComponent;
class UCameraComponent;
class UHPComponent;
class UInventoryComponent;

UCLASS(Blueprintable)
class AClicker2Character : public ACharacter
{
	GENERATED_BODY()

public:
	AClicker2Character(const FObjectInitializer& ObjectInitializer);

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Player", meta=(AllowPrivateAccess = "true"))
	FVector NewHpBarRelativePosition;

	UPROPERTY(VisibleAnywhere, Category = "Player", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UHPComponent> ActorHP;
	
	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> InventoryComp;

	UPROPERTY(VisibleAnywhere, Category = "Statistic", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerStatsComponent> PlayerStatistic;

	UPROPERTY(VisibleAnywhere, Category = "Loot component", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USearchForPickupColliderComponent> PickupItemsComponent;

public:
	USearchForPickupColliderComponent* GetSearchItemComponent() const;
	UInventoryComponent* GetInventoryComponent() const;
	UPlayerStatsComponent* GetStatsComponent() const;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<UGunItemdata> TestItem;

	virtual void BeginPlay() override;
	
};
