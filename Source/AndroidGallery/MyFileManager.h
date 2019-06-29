// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "MyFileManager.generated.h"

/**
 * 
 */
UCLASS()
class ANDROIDGALLERY_API UMyFileManager : public UObject
{
	GENERATED_BODY()
	
public:

	UMyFileManager(const FObjectInitializer & ObjectInitializer);

	void GoIntoCatalog(const FString& CatalogFullPath, const FString& CatalogName);

	void SetRootGalleryPath(const FString& Path);

	const FString& GetConcatenator() const;

	void ReturnFromPhotoViewer();

	UTexture2D* GetTexture(const FString& FileFullPath);

private:

	FString m_RootGalleryPath;
	FString m_Concatenator;
	FString m_ParentDirectoryPath;
	FString m_CurrentDirectoryRelativePath;
	FString m_PhotoViewerFullPath;

	TArray<FString> m_ChildCatalogNames;
	TArray<FString> m_FileNames;

	bool IsCatalogInsideExist(const FString& Path);
	bool IsFileInsideExist(const FString& Path);

	//	true for catalogs, false for files
	void LookForContent(const FString& Path, bool Catalog);

	EImageFormat GetImageFormat(const FString& FileFullPath);

	void ShowPhotosFromDirectory(const FString& CatalogFullPath);
	void GoToParentDirectory(const FString& CurrentCatalogFullPath);
	void ShowInternalDirectories(const FString& CurrentCatalogFullPath);
};
