// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AndroGallery.h"

//#define LOCTEXT_NAMESPACE "FAndroGalleryModule"
#define LOCTEXT_NAMESPACE "AndroGallery"


#if PLATFORM_ANDROID
#include "AndroidGateway.h"
#endif

FAndroGalleryModule* androModule = nullptr;

void FAndroGalleryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
#if PLATFORM_ANDROID
//	m_AndroidGatewayPtr = MakeShareable(new FAndroidGateway());
	androModule = &FModuleManager::LoadModuleChecked<FAndroGalleryModule>("AndroGallery");
#endif
}

void FAndroGalleryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
//	m_AndroidGatewayPtr.Reset();
	androModule = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAndroGalleryModule, AndroGallery)