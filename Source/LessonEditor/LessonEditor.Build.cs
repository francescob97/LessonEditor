// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LessonEditor : ModuleRules
{
	public LessonEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "EnhancedInput",
                "Slate",
                "SlateCore",
                "UMG", // se usi UUserWidget o UI in generale
                "DesktopPlatform",
                "XmlParser"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[] 
            { 
                "Slate", 
                "SlateCore", 
                "XmlParser", 
                "DesktopPlatform",
                "EditorStyle"
            });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
