// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CC_And_IF : ModuleRules
{
	public CC_And_IF(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CC_And_IF",
			"CC_And_IF/Variant_Platforming",
			"CC_And_IF/Variant_Platforming/Animation",
			"CC_And_IF/Variant_Combat",
			"CC_And_IF/Variant_Combat/AI",
			"CC_And_IF/Variant_Combat/Animation",
			"CC_And_IF/Variant_Combat/Gameplay",
			"CC_And_IF/Variant_Combat/Interfaces",
			"CC_And_IF/Variant_Combat/UI",
			"CC_And_IF/Variant_SideScrolling",
			"CC_And_IF/Variant_SideScrolling/AI",
			"CC_And_IF/Variant_SideScrolling/Gameplay",
			"CC_And_IF/Variant_SideScrolling/Interfaces",
			"CC_And_IF/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
