// Fill out your copyright notice in the Description page of Project Settings.


#include "Player\HPComponent.h"
#include "Components\WidgetComponent.h"
#include "UI\HPBar.h"

// Sets default values for this component's properties
UHPComponent::UHPComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	HPRegenPerSec = 1.f;
	CurrentHp = 0;
	MaxHp = 100;
	// ...


	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
	Widget->SetDrawAtDesiredSize(true);
	Widget->SetupAttachment(this);
}


// Called when the game starts
void UHPComponent::BeginPlay()
{
	Super::BeginPlay();
	Widget->SetWidgetClass(HealthBar);
	Widget->InitWidget();
	UHPBar* bar = Cast<UHPBar>(Widget->GetUserWidgetObject());

	if (bar != nullptr)
	{
		bar->SetHealthComponent(this);
	}

	// ...
}


void UHPComponent::RegenerateHP(float DeltaTime)
{
	if (CurrentHp < MaxHp)
	{
		HPRegenTicker += DeltaTime * GetHPRegenPerSec();
		int howMany = static_cast<int>(HPRegenTicker);

		if (howMany >= 1)
		{
			Heal(howMany);
			HPRegenTicker -= howMany;
		}
	}
	else
	{
		HPRegenTicker = 0;
	}
}

// Called every frame
void UHPComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RegenerateHP(DeltaTime);
}

int UHPComponent::GetCurrentHp()
{
	return CurrentHp;
}

int UHPComponent::GetMaxHp()
{
	return MaxHp;
}

float UHPComponent::GetHPRegenPerSec()
{
	return HPRegenPerSec;
}

void UHPComponent::SetMaxHp(int newMaxHp)
{
	int diff = newMaxHp - MaxHp;
	MaxHp = newMaxHp;

	if (diff > 0)
	{
		CurrentHp += diff;
	}
	else
	{
		if (CurrentHp > newMaxHp)
		{
			CurrentHp = newMaxHp;
		}
	}
}

int UHPComponent::Heal(int HPToAdd)
{
	const int diff = MaxHp - CurrentHp;
	int healed;

	if (diff > HPToAdd)
	{
		healed = HPToAdd;
	}
	else
	{
		healed = diff;
	}

	CurrentHp += healed;

	return healed;
}

void UHPComponent::DealDamage(int Damage)
{
	CurrentHp -= Damage;
}
