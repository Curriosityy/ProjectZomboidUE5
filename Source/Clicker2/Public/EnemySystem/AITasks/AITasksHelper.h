#pragma once

class AITasksHelper
{
public
:
	struct FRaycastsInfo
	{
		float SearchDistance{500.f};
		float SeeAngle{45.f};
		int RayCount{8};

		FRaycastsInfo(float searchDistance, float seeAngle, int rayCount): SearchDistance(searchDistance),
		                                                                   SeeAngle(seeAngle), RayCount(rayCount)
		{
		}

		FRaycastsInfo()
		{
		}
	};

	void static GetClosestPlayersInRange(UWorld* world, ACharacter* character, TArray<FHitResult>& closestHit,
	                                     FRaycastsInfo raycastsInfo);
};
