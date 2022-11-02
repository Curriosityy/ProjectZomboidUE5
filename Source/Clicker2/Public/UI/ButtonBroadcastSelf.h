// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components\Button.h"
#include "ButtonBroadcastSelf.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClickedEventSelf, UButton*, Sender);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonPressedEventSelf, UButton*, Sender);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonReleasedEventSelf, UButton*, Sender);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonHoverEventSelf, UButton*, Sender);

/**
 * 
 */
UCLASS()
class CLICKER2_API UButtonBroadcastSelf : public UButton
{
	GENERATED_BODY()

public:
	UButtonBroadcastSelf();

	FOnButtonClickedEventSelf OnClickedSelf;
	FOnButtonPressedEventSelf OnPressedSelf;
	FOnButtonReleasedEventSelf OnReleasedSelf;
	FOnButtonHoverEventSelf OnHoveredSelf;

private:
	UFUNCTION()
	void OnClickedSelfBroadcast();

	UFUNCTION()
	void OnPressedSelfBroadcast();

	UFUNCTION()
	void OnReleasedSelfBroadcast();

	UFUNCTION()
	void OnHoveredSelfBroadcast();
};
