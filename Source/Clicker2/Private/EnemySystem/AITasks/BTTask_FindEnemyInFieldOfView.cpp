// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySystem\AITasks\BTTask_FindEnemyInFieldOfView.h"

#include "AIController.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "EnemySystem\Enemy.h"
#include "EnemySystem\AITasks\AITasksHelper.h"
#include "Player\Clicker2Character.h"

UBTTask_FindEnemyInFieldOfView::UBTTask_FindEnemyInFieldOfView()
{
	NodeName = TEXT("Find Enemy In Range");

	TSubclassOf<ACharacter> defaultClass{};
	BlackboardKey.AddObjectFilter(this,GET_MEMBER_NAME_CHECKED(UBTTask_FindEnemyInFieldOfView, BlackboardKey),
	                              defaultClass);
}

ACharacter* UBTTask_FindEnemyInFieldOfView::GetClosesEnemy(TArray<FHitResult>& Array)
{
	float closest = 10000.f;
	AActor* closestActor = nullptr;
	for (FHitResult& hit : Array)
	{
		if (hit.Distance < closest)
		{
			closest = hit.Distance;
			closestActor = hit.GetActor();
		}
	}

	return Cast<ACharacter>(closestActor);
}


EBTNodeResult::Type UBTTask_FindEnemyInFieldOfView::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* aiController{OwnerComp.GetAIOwner()};
	ACharacter* aiCharacter{aiController->GetPawn<ACharacter>()};

	TArray<FHitResult> closestHits{};

	AITasksHelper::GetClosestPlayersInRange(GetWorld(), aiCharacter, closestHits, {SearchDistance, SeeAngle, RayCount});
	ACharacter* closestHit{};

	if (closestHits.Num() > 0)
	{
		closestHit = GetClosesEnemy(closestHits);
	}

	aiController->GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, closestHit);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}

FString UBTTask_FindEnemyInFieldOfView::GetStaticDescription() const
{
	return FString::Printf(TEXT("Object: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
