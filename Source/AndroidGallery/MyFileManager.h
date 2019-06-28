// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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

private:

	FString m_RootGalleryPath;
	FString m_Concatenator;
	FString m_ParentDirectoryPath;
	FString m_CurrentDirectoryPath;

	TArray<FString> m_ChildCatalogNames;
	TArray<FString> m_FilNames;

	bool IsCatalogInsideExist(const FString& Path);
	bool IsFileInsideExist(const FString& Path);

	//	true for catalogs, false for files
	void LookForContent(const FString& Path, bool Catalog);
};
