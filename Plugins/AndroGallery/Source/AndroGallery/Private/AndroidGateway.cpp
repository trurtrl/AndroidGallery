#include "../Public/AndroidGateway.h"
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#include "AndroidPermission/Classes/AndroidPermissionCallbackProxy.h"

#if PLATFORM_ANDROID
#include "AndroidPlatform.h"
#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include <android_native_app_glue.h>
#endif


FAndroidGateway::FAndroidGateway()
	: m_StoragePermission("android.permission.READ_EXTERNAL_STORAGE")
{

}

void FAndroidGateway::AskGalleryRootPath()
{
	if (CheckPermissionToReadStorage())
	{
		OnExternalStoragePath.Broadcast(AskPath());
	}
	else
	{
		AskPermissionToReadStorage();
	}
}

bool FAndroidGateway::CheckPermissionToReadStorage()
{
	return UAndroidPermissionFunctionLibrary::CheckPermission(m_StoragePermission);
}

void FAndroidGateway::AskPermissionToReadStorage()
{
	TArray<FString> permissions;
	permissions.Add(m_StoragePermission);
	static UAndroidPermissionCallbackProxy* permissionProxy = UAndroidPermissionFunctionLibrary::AcquirePermissions(permissions);
	if (permissionProxy)
	{
		if (!permissionProxy->OnPermissionsGrantedDynamicDelegate.IsBound())
		{
			permissionProxy->OnPermissionsGrantedDynamicDelegate.AddDynamic(this, &FAndroidGateway::OnPermissionGrantedHandle);
		}
	}
}

void FAndroidGateway::OnPermissionGrantedHandle(const TArray<FString>& Permissions, const TArray<bool>& GrantResults)
{
	FString path = "";
	for (int32 i = 0; i < Permissions.Num(); ++i)
	{
		if (Permissions[i] == m_StoragePermission && GrantResults[i] == true)
		{
			path = AskPath();
		}
	}
	OnExternalStoragePath.Broadcast(path);
}

FString FAndroidGateway::AskPath()
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