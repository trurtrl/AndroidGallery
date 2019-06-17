#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
//#include "EngineMinimal.h"
#include "AndroidGateway.h"


typedef TSharedPtr<FAndroidGateway, ESPMode::ThreadSafe> FAndroidGatewayPtr;

class FAndroGalleryInterface : public IModuleInterface
{
public:
    
    static inline FAndroGalleryInterface& Get()
    {
        return FModuleManager::GetModuleChecked<FAndroGalleryInterface>("AndroGallery");
    }
    
    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("AndroGallery");
    }
    
    inline FAndroidGatewayPtr GetGateway() const 
    {
        return m_AndroidGatewayPtr;
    }
    
protected:
    
    FAndroidGatewayPtr m_AndroidGatewayPtr;
    
};
