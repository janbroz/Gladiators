// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Gladiators : ModuleRules
{
	public Gladiators(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "UMG"
            }
        );

		PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Slate",
                "SlateCore",
                "OnlineSubsystem",
                "OnlineSubsystemUtils"
            }
        );

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		//PrivateDependencyModuleNames.Add("OnlineSubsystem");
        DynamicallyLoadedModuleNames.AddRange(
            new string[]{
                "OnlineSubsystemNull"
            }
        );

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
