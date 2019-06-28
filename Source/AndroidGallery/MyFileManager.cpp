// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFileManager.h"
#include "Runtime/Core/Public/HAL/FileManager.h"

UMyFileManager::UMyFileManager()
	: Super()
	, m_CurrentCatalog("/*")
{

}

bool UMyFileManager::IsCatalogInsideExist(const FString& Path)
{
	LookForContent(Path, true);

	return m_CatalogNames.Num();
}

bool UMyFileManager::IsFileInsideExist(const FString& Path)
{
	LookForContent(Path, false);

	return m_FilNames.Num();
}

void UMyFileManager::LookForContent(const FString& Path, bool Catalog)
{
	IFileManager& FileMgr = IFileManager::Get();
	if (FileMgr.DirectoryExists(*Path))
	{
		FString currentPath = Path / TEXT("*");
		if (Catalog)
		{
			m_CatalogNames.Empty();
			FileMgr.FindFiles(m_CatalogNames, *currentPath, false, true);
		}
		else
		{
			m_FilNames.Empty();
			FileMgr.FindFiles(m_FilNames, *currentPath, true, false);
		}
	}
}

const TArray<FString>& UMyFileManager::GetCatalogNames() const
{
	return m_CatalogNames;
}

const TArray<FString>& UMyFileManager::GetFileNames() const
{
	return m_FilNames;
}