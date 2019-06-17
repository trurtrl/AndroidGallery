#pragma once

#include "CoreMinimal.h"
//#include "EngineMinimal.h"
//#include "Core.h"

//#if PLATFORM_ANDROID
//#include "AndroidPlatform.h"
//#include "Android/AndroidJava.h"
//#include "Android/AndroidApplication.h"
//#include "Android/AndroidJNI.h"
//#include <android_native_app_glue.h>
//#endif


class ANDROGALLERY_API FAndroidGateway
{
public:

    FAndroidGateway();
 
    FString GetGalleryRootPath();

//#if PLATFORM_ANDROID
//	// JNI Methods
//	static jmethodID GetGalleryRootPathMethod;
//#endif
    
};
