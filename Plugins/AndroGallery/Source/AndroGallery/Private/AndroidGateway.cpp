#include "../Public/AndroidGateway.h"

#if PLATFORM_ANDROID
#include "AndroidPlatform.h"
#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include <android_native_app_glue.h>
#endif


//#if PLATFORM_ANDROID
//	// JNI Methods
//	jmethodID FAndroidGateway::GetGalleryRootPathMethod;
//#endif


FAndroidGateway::FAndroidGateway()
{
//#if PLATFORM_ANDROID
//		if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
//		{
//			GetGalleryRootPathMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getGalleryRootPath", "()Z", false);
//		}
//#endif
}

FString FAndroidGateway::GetGalleryRootPath()
{
    FString path = "";
    
#if PLATFORM_ANDROID
		if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
		{
			jmethodID GetGalleryRootPathMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getGalleryRootPath", "()Z", false);
			jstring jPath = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, GetGalleryRootPathMethod);
			if (jPath != NULL)
			{
				const char* charArray = Env->GetStringUTFChars(jPath, 0);
				path = FString(UTF8_TO_TCHAR(charArray));

				Env->ReleaseStringUTFChars(jPath, charArray);
				Env->DeleteLocalRef(jPath);
			}            
		}
#endif
    return path;
}
