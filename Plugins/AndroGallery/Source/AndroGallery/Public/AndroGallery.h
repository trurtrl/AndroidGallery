// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AndroGalleryInterface.h"

class FAndroGalleryModule : public FAndroGalleryInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
