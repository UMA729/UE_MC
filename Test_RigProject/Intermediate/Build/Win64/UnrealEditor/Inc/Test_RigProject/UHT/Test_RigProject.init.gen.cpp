// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTest_RigProject_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Test_RigProject;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Test_RigProject()
	{
		if (!Z_Registration_Info_UPackage__Script_Test_RigProject.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Test_RigProject",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x49DFA728,
				0x1D7CAE25,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Test_RigProject.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Test_RigProject.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Test_RigProject(Z_Construct_UPackage__Script_Test_RigProject, TEXT("/Script/Test_RigProject"), Z_Registration_Info_UPackage__Script_Test_RigProject, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x49DFA728, 0x1D7CAE25));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
