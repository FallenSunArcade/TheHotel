// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HTL : ModuleRules
{
	public HTL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
			"HeadMountedDisplay", "EnhancedInput", "UMG", "NavigationSystem", "FieldSystemEngine",
			"AIModule", "GameplayTasks", "StateTreeModule", "Niagara", "GeometryCollectionEngine", "ChaosSolverEngine" });
		
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
