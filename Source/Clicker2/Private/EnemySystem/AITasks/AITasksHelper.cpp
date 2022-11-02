#include "EnemySystem\AITasks\AITasksHelper.h"

#include "GameFramework\Character.h"
#include "Player\Clicker2Character.h"

void AITasksHelper::GetClosestPlayersInRange(UWorld* world, ACharacter* character, TArray<FHitResult>& closestHit,
                                             FRaycastsInfo raycastsInfo)
{
	FVector seeLocation{character->GetMesh()->GetSocketLocation("HeadSocket")};
	FVector forwardVector{character->GetActorForwardVector()};
	FVector upVector{character->GetActorUpVector()};
	FVector leftSeeVector{forwardVector.RotateAngleAxis(-(raycastsInfo.SeeAngle / 2), upVector)};

	float stepAngle{raycastsInfo.SeeAngle / raycastsInfo.RayCount};

	TArray<FHitResult> results{};

	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(character);

	for (int i = 0; i < raycastsInfo.RayCount; i++)
	{
		FVector finalSeeVector{leftSeeVector.RotateAngleAxis(stepAngle * i, upVector)};

		world->LineTraceMultiByChannel(results, seeLocation, seeLocation + finalSeeVector * raycastsInfo.SearchDistance,
		                               ECC_GameTraceChannel4, Params);
		if (results.Num() > 0)
		{
			FHitResult* closestEnemy = results.FindByPredicate([](FHitResult& result)
			{
				return Cast<AClicker2Character>(result.GetActor()) != nullptr;
			});

			if (closestEnemy)
			{
				closestHit.Add(*closestEnemy);
			}
		}

		DrawDebugLine(world, seeLocation, seeLocation + finalSeeVector * raycastsInfo.SearchDistance, FColor::Red);
	}
}
