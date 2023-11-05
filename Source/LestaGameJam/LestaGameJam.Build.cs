// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LestaGameJam : ModuleRules
{
	public LestaGameJam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"Niagara",
			"GameplayTasks",
			"PhysicsCore",
			"NavigationSystem",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate","SlateCore"  });
		
		PublicIncludePaths.AddRange(new string[] { 
			"LestaGameJam/Public/Player",
			"LestaGameJam/Public/UI",
		});
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
