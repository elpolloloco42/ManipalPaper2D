// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Paper2DTestReseau : ModuleRules
{
	public Paper2DTestReseau(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore" });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "Sockets", "Networking" });
		
		// Uncomment if you are using online features
		PrivateDependencyModuleNames.Add("OnlineSubsystem");

		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");


		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
