// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TowerGame/Public/TGActorBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTGActorBase() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
TOWERGAME_API UClass* Z_Construct_UClass_ATGActorBase();
TOWERGAME_API UClass* Z_Construct_UClass_ATGActorBase_NoRegister();
UPackage* Z_Construct_UPackage__Script_TowerGame();
// End Cross Module References

// Begin Class ATGActorBase
void ATGActorBase::StaticRegisterNativesATGActorBase()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATGActorBase);
UClass* Z_Construct_UClass_ATGActorBase_NoRegister()
{
	return ATGActorBase::StaticClass();
}
struct Z_Construct_UClass_ATGActorBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "TGActorBase.h" },
		{ "ModuleRelativePath", "Public/TGActorBase.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATGActorBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ATGActorBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_TowerGame,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATGActorBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ATGActorBase_Statics::ClassParams = {
	&ATGActorBase::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATGActorBase_Statics::Class_MetaDataParams), Z_Construct_UClass_ATGActorBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ATGActorBase()
{
	if (!Z_Registration_Info_UClass_ATGActorBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATGActorBase.OuterSingleton, Z_Construct_UClass_ATGActorBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ATGActorBase.OuterSingleton;
}
template<> TOWERGAME_API UClass* StaticClass<ATGActorBase>()
{
	return ATGActorBase::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ATGActorBase);
ATGActorBase::~ATGActorBase() {}
// End Class ATGActorBase

// Begin Registration
struct Z_CompiledInDeferFile_FID_NBC_8_Project_8th_Team13_CH3_Project_TowerGame_Source_TowerGame_Public_TGActorBase_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ATGActorBase, ATGActorBase::StaticClass, TEXT("ATGActorBase"), &Z_Registration_Info_UClass_ATGActorBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATGActorBase), 1326813595U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_NBC_8_Project_8th_Team13_CH3_Project_TowerGame_Source_TowerGame_Public_TGActorBase_h_1248609144(TEXT("/Script/TowerGame"),
	Z_CompiledInDeferFile_FID_NBC_8_Project_8th_Team13_CH3_Project_TowerGame_Source_TowerGame_Public_TGActorBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_NBC_8_Project_8th_Team13_CH3_Project_TowerGame_Source_TowerGame_Public_TGActorBase_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
