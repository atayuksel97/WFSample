// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UAISample : ModuleRules
{
	public UAISample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "WiseFeline", "NavigationSystem" });
	}
}