// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Test_RigProject/MyPawn.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyPawn() {}

// Begin Cross Module References
CONTROLRIG_API UClass* Z_Construct_UClass_UControlRig_NoRegister();
CONTROLRIG_API UClass* Z_Construct_UClass_UControlRigComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_APawn();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCapsuleComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
TEST_RIGPROJECT_API UClass* Z_Construct_UClass_AMyPawn();
TEST_RIGPROJECT_API UClass* Z_Construct_UClass_AMyPawn_NoRegister();
UPackage* Z_Construct_UPackage__Script_Test_RigProject();
// End Cross Module References

// Begin Class AMyPawn
void AMyPawn::StaticRegisterNativesAMyPawn()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMyPawn);
UClass* Z_Construct_UClass_AMyPawn_NoRegister()
{
	return AMyPawn::StaticClass();
}
struct Z_Construct_UClass_AMyPawn_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "MyPawn.h" },
		{ "ModuleRelativePath", "MyPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_mCapsule_MetaData[] = {
		{ "Category", "C_CODE" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MyPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_mSMesh_MetaData[] = {
		{ "Category", "C_CODE" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbdJ\xef\xbf\xbdv\xef\xbf\xbdZ\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdR\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd|\xef\xbf\xbd[\xef\xbf\xbdl\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdg\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MyPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbdJ\xef\xbf\xbdv\xef\xbf\xbdZ\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdR\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd|\xef\xbf\xbd[\xef\xbf\xbdl\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdg" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_mSpringArm_MetaData[] = {
		{ "Category", "C_CODE" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbdX\xef\xbf\xbdP\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd^\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd""b\xef\xbf\xbdV\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdR\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd|\xef\xbf\xbd[\xef\xbf\xbdl\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdg\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MyPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbdX\xef\xbf\xbdP\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd^\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd""b\xef\xbf\xbdV\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdR\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd|\xef\xbf\xbd[\xef\xbf\xbdl\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdg" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_mCamera_MetaData[] = {
		{ "Category", "C_CODE" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbdX\xef\xbf\xbdv\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdO\xef\xbf\xbd""A\xef\xbf\xbd[\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdR\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd|\xef\xbf\xbd[\xef\xbf\xbdl\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdg\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MyPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbdX\xef\xbf\xbdv\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdO\xef\xbf\xbd""A\xef\xbf\xbd[\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdR\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd|\xef\xbf\xbd[\xef\xbf\xbdl\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdg" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_mControlRig_MetaData[] = {
		{ "Category", "C_CODE" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbdJ\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdR\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd|\xef\xbf\xbd[\xef\xbf\xbdl\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdg\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MyPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbdJ\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdR\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd|\xef\xbf\xbd[\xef\xbf\xbdl\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdg" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ControlRig_MetaData[] = {
		{ "Category", "Rig" },
		{ "ModuleRelativePath", "MyPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_mIM_Key_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "MyPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_mIA_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "MyPawn.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_mCapsule;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_mSMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_mSpringArm;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_mCamera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_mControlRig;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ControlRig;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_mIM_Key;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_mIA;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyPawn>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyPawn_Statics::NewProp_mCapsule = { "mCapsule", nullptr, (EPropertyFlags)0x01140000000a000d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyPawn, mCapsule), Z_Construct_UClass_UCapsuleComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_mCapsule_MetaData), NewProp_mCapsule_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyPawn_Statics::NewProp_mSMesh = { "mSMesh", nullptr, (EPropertyFlags)0x01140000000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyPawn, mSMesh), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_mSMesh_MetaData), NewProp_mSMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyPawn_Statics::NewProp_mSpringArm = { "mSpringArm", nullptr, (EPropertyFlags)0x01140000000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyPawn, mSpringArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_mSpringArm_MetaData), NewProp_mSpringArm_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyPawn_Statics::NewProp_mCamera = { "mCamera", nullptr, (EPropertyFlags)0x01140000000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyPawn, mCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_mCamera_MetaData), NewProp_mCamera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyPawn_Statics::NewProp_mControlRig = { "mControlRig", nullptr, (EPropertyFlags)0x01140000000a000d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyPawn, mControlRig), Z_Construct_UClass_UControlRigComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_mControlRig_MetaData), NewProp_mControlRig_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyPawn_Statics::NewProp_ControlRig = { "ControlRig", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyPawn, ControlRig), Z_Construct_UClass_UControlRig_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ControlRig_MetaData), NewProp_ControlRig_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyPawn_Statics::NewProp_mIM_Key = { "mIM_Key", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyPawn, mIM_Key), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_mIM_Key_MetaData), NewProp_mIM_Key_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyPawn_Statics::NewProp_mIA = { "mIA", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyPawn, mIA), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_mIA_MetaData), NewProp_mIA_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMyPawn_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyPawn_Statics::NewProp_mCapsule,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyPawn_Statics::NewProp_mSMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyPawn_Statics::NewProp_mSpringArm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyPawn_Statics::NewProp_mCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyPawn_Statics::NewProp_mControlRig,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyPawn_Statics::NewProp_ControlRig,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyPawn_Statics::NewProp_mIM_Key,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyPawn_Statics::NewProp_mIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyPawn_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AMyPawn_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APawn,
	(UObject* (*)())Z_Construct_UPackage__Script_Test_RigProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyPawn_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyPawn_Statics::ClassParams = {
	&AMyPawn::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AMyPawn_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AMyPawn_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyPawn_Statics::Class_MetaDataParams), Z_Construct_UClass_AMyPawn_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMyPawn()
{
	if (!Z_Registration_Info_UClass_AMyPawn.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyPawn.OuterSingleton, Z_Construct_UClass_AMyPawn_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMyPawn.OuterSingleton;
}
template<> TEST_RIGPROJECT_API UClass* StaticClass<AMyPawn>()
{
	return AMyPawn::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMyPawn);
AMyPawn::~AMyPawn() {}
// End Class AMyPawn

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_GA2B_Desktop_Test_RigProject_Source_Test_RigProject_MyPawn_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyPawn, AMyPawn::StaticClass, TEXT("AMyPawn"), &Z_Registration_Info_UClass_AMyPawn, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyPawn), 109658081U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_GA2B_Desktop_Test_RigProject_Source_Test_RigProject_MyPawn_h_1007090781(TEXT("/Script/Test_RigProject"),
	Z_CompiledInDeferFile_FID_Users_GA2B_Desktop_Test_RigProject_Source_Test_RigProject_MyPawn_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_GA2B_Desktop_Test_RigProject_Source_Test_RigProject_MyPawn_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
