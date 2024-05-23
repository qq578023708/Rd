// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Rd : ModuleRules
{
	public Rd(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[]
		{
			"Rd"
		});

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			"GameFeatures",
			"ModularGameplay",
			"GameplayTags",
			"GameplayAbilities"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"UMG",
			"CommonUI",
			"UIExtension",
			"CommonGame",
			"InputCore",
			"Slate",
			"SlateCore"
		});
	}
}
