#pragma once

//#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "Core.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExternalStoragePath, const FString, Path);

class ANDROGALLERY_API FAndroidGateway
{
public:

    FAndroidGateway();
 
    void AskGalleryRootPath();

	FOnExternalStoragePath OnExternalStoragePath;
   
	UFUNCTION()
	void OnPermissionGrantedHandle(const TArray<FString>& Permissions, const TArray<bool>& GrantResults);

private:

	FString m_StoragePermission;

	bool CheckPermissionToReadStorage();
	void AskPermissionToReadStorage();
	FString AskPath();

};
