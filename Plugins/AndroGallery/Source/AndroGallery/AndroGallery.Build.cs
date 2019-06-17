// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

//using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{
    public class AndroGallery : ModuleRules
    {
        public AndroGallery(ReadOnlyTargetRules Target) : base(Target)
        {
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

            PublicIncludePaths.AddRange(
                new string[] {
                    // ... add public include paths required here ...
                }
                );


            PrivateIncludePaths.AddRange(
                new string[] {
				// ... add other private include paths required here ...
                //"Source/Runtime/Launch/Private",
                "AndroGallery/Private",
                }
                );


            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                "Core",
                "Engine",
                    // ... add other public dependencies that you statically link with here ...
                }
                );


            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
//				"CoreUObject",
				"Engine",
                    //				"Slate",
                    //				"SlateCore",
                    // ... add private dependencies that you statically link with here ...	
                }
                );


            DynamicallyLoadedModuleNames.AddRange(
                new string[]
                {
                    // ... add any modules that your module loads dynamically here ...
                }
                );

            // For Android
            if (Target.Platform == UnrealTargetPlatform.Android)
            {
                PrivateIncludePaths.Add("AndroGallery/Private");

                PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });

                string PluginRelativePath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginRelativePath, "AndroGalleryAPL.xml"));
            }
        }
    }
}