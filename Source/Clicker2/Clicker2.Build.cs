// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Clicker2 : ModuleRules
{
	public Clicker2(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new[] { "AnimGraphRuntime", "WebRTC" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule",
			"Niagara", "UnrealEd", "GameplayTasks"
		});
	}
}
