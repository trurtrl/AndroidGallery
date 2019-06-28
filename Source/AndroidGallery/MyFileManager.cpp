// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFileManager.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "Engine/Engine.h"


void UMyFileManager::GoIntoCatalog(const FString& Path)
{
	if (Path != "")
	{
		bool catalogIsEmpty = true;
		if (IsCatalogInsideExist(Path))
		{
			for (FString name : m_CatalogNames)
			{
				if (name.Left(1) != ".")
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Catalog : %s"), *name));
				}
			}
			catalogIsEmpty = false;
		}
		if (IsFileInsideExist(Path))
		{
			for (FString name : m_FilNames)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("File : %s"), *name));
			}
			catalogIsEmpty = false;
		}
		if (catalogIsEmpty)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("catalog : %s is empty"), *Path));
		}
	}
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
