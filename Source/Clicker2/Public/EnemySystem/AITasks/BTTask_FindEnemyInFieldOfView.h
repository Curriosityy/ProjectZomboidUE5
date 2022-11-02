// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree\Tasks\BTTask_BlackboardBase.h"
#include "BTTask_FindEnemyInFieldOfView.generated.h"

/**
 * 
 */
UCLASS()
class CLICKER2_API UBTTask_FindEnemyInFieldOfView : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SearchDistance{500.f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SeeAngle{45.f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RayCount{8};

public:
	UBTTask_FindEnemyInFieldOfView();

	ACharacter* GetClosesEnemy(TArray<FHitResult>& Array);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;
};
