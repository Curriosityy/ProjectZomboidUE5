// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

class UBehaviorTreeComponent;
class UBehaviorTree;
/**
 * 
 */
UCLASS()
class CLICKER2_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	//UPROPERTY(VisibleAnywhere)
	//TObjectPtr<UBlackboardComponent> BlackboardComponent;

public:
	AZombieAIController();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
};
