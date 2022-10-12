// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatsUserWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class CLICKER2_API UPlayerStatsUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Nickname;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Strength;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Agility;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> MeleeAim;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> RifleAim;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Maintenance;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Gathering;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Fishing;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Foraging;

public:
	//TODO:
	//void Setup(UActorComponent* statsComp);
	
};
