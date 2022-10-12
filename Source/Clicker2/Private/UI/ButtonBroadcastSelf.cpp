// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ButtonBroadcastSelf.h"

UButtonBroadcastSelf::UButtonBroadcastSelf()
{
	OnClicked.AddDynamic(this, &UButtonBroadcastSelf::OnClickedSelfBroadcast);
	OnPressed.AddDynamic(this, &UButtonBroadcastSelf::OnPressedSelfBroadcast);
	OnReleased.AddDynamic(this, &UButtonBroadcastSelf::OnReleasedSelfBroadcast);
	OnHovered.AddDynamic(this, &UButtonBroadcastSelf::OnHoveredSelfBroadcast);
}

void UButtonBroadcastSelf::OnClickedSelfBroadcast()
{
	OnClickedSelf.Broadcast(this);
}

void UButtonBroadcastSelf::OnPressedSelfBroadcast()
{
	OnPressedSelf.Broadcast(this);
}

void UButtonBroadcastSelf::OnReleasedSelfBroadcast()
{
	OnReleasedSelf.Broadcast(this);
}

void UButtonBroadcastSelf::OnHoveredSelfBroadcast()
{
	OnHoveredSelf.Broadcast(this);
}
