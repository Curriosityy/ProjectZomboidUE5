// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySystem\ZombieAIController.h"

#include "BehaviorTree\BehaviorTree.h"
#include "BehaviorTree\BehaviorTreeComponent.h"
#include "BehaviorTree\BlackboardComponent.h"

AZombieAIController::AZombieAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	//BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void AZombieAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}
}

void AZombieAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree && Blackboard)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}
