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

	void GoIntoCatalog(const FString& Path);

private:

	TArray<FString> m_CatalogNames;
	TArray<FString> m_FilNames;

	bool IsCatalogInsideExist(const FString& Path);
	bool IsFileInsideExist(const FString& Path);

	//	true for catalogs, false for files
	void LookForContent(const FString& Path, bool Catalog);
};
