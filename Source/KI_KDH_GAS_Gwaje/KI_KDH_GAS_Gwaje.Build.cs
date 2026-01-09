// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KI_KDH_GAS_Gwaje : ModuleRules
{
	public KI_KDH_GAS_Gwaje(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara" });
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks", "UMG" });
    }
}
