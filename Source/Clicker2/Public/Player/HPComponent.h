// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HPComponent.generated.h"

class UHPBar;
class UWidgetComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class CLICKER2_API UHPComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHPComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void RegenerateHP(float DeltaTime);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	int GetCurrentHp();

	UFUNCTION(BlueprintCallable)
	int GetMaxHp();

	UFUNCTION(BlueprintCallable)
	float GetHPRegenPerSec();

	UFUNCTION(BlueprintCallable)
	void SetMaxHp(int newMaxHp);

	UFUNCTION(BlueprintCallable)
	int Heal(int HPToAdd);

	UFUNCTION(BlueprintCallable)
	void DealDamage(int damage);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "HPValues")
	int MaxHp;

	UPROPERTY(VisibleAnywhere, Category = "HPValues")
	int CurrentHp;

	UPROPERTY(EditDefaultsOnly, Category = "HPValues")
	float HPRegenPerSec;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHPBar> HealthBar;

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	TObjectPtr<UWidgetComponent> Widget;

private:
	float HPRegenTicker;
};
