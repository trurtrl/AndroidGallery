// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFileManager.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "UI/AGHUD.h"
#include "Engine/Engine.h"
#include "Runtime/Core/Public/Misc/Paths.h"


UMyFileManager::UMyFileManager(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, m_RootGalleryPath("")
	, m_Concatenator("/")
	, m_ParentDirectoryPath("..")
	, m_CurrentDirectoryPath(".")
{

}

void UMyFileManager::GoIntoCatalog(const FString& CatalogFullPath, const FString& CatalogName)
{
	AAGHUD* HUD = Cast<AAGHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUD && CatalogFullPath != "")
	{
		if (CatalogName == m_CurrentDirectoryPath)
		{
			// show current catalog's content
			if (IsFileInsideExist(CatalogFullPath))
			{
				for (FString name : m_FilNames)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("File : %s"), *name));
				}
			}
		}
		else
		{
			FString catalogFullPath = CatalogFullPath;
			catalogFullPath.RemoveFromEnd(m_Concatenator);

			FString fullPath = "";
			if (CatalogName == m_ParentDirectoryPath)
			{
				FString parentPath = "";
				if (m_RootGalleryPath == catalogFullPath)
				{
					//	prevent to go out of accessed catalog
					parentPath = catalogFullPath;
				}
				else
				{
					//	get parent
					parentPath = FPaths::GetPath(catalogFullPath);
					//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Catalog : %s"), *catalogFullPath));
					//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Parent : %s"), *parentPath));
				}
				GoIntoCatalog(parentPath, "");
			}
			else
			{
				fullPath = catalogFullPath + m_Concatenator + CatalogName;

				HUD->CreateWindow(EWidgeTType::CatalogViewer);
				HUD->ClearCatalogListWidget();

				if (IsCatalogInsideExist(fullPath))
				{
					for (int32 i = 0; i < m_ChildCatalogNames.Num(); ++i)
					{
						//	if catalog's name begins with "."
						if (m_ChildCatalogNames[i].Left(1) == ".")
						{
							m_ChildCatalogNames.RemoveAt(i);
						}
					}

					HUD->AddCatalogToCatalogListWidget(fullPath, m_ChildCatalogNames);
				}
				else
				{
					//	if within the catalog is no a sub-catalog
					HUD->AddCatalogToCatalogListWidget(fullPath, m_ParentDirectoryPath);
					HUD->AddCatalogToCatalogListWidget(fullPath, m_CurrentDirectoryPath);
				}
			}
		}
	}
}

bool UMyFileManager::IsCatalogInsideExist(const FString& Path)
{
	LookForContent(Path, true);

	return m_ChildCatalogNames.Num();
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
			m_ChildCatalogNames.Empty();
			FileMgr.FindFiles(m_ChildCatalogNames, *currentPath, false, true);
		}
		else
		{
			m_FilNames.Empty();
			FileMgr.FindFiles(m_FilNames, *currentPath, true, false);
		}
	}
}

void UMyFileManager::SetRootGalleryPath(const FString& Path)
{
	m_RootGalleryPath = Path;
}

const FString& UMyFileManager::GetConcatenator() const
{
	return m_Concatenator;
}