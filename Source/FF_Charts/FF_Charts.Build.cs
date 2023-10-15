// Some copyright should be here...

using System;
using System.IO;
using UnrealBuildTool;

public class FF_Charts : ModuleRules
{
	public FF_Charts(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        if (UnrealTargetPlatform.Win64 == Target.Platform)
        {
            string Include_Matplot = "../Source/FF_Charts/ThirdParty/matplot/Windows/include";
            PrivateIncludePaths.Add(Include_Matplot);

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty", "matplot", "Windows", "lib", "matplot.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty", "matplot", "Windows", "lib", "nodesoup.lib"));
        }

        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UMG"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}