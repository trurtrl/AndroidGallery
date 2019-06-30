// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFileManager.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "UI/AGHUD.h"
#include "Engine/Engine.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"


UMyFileManager::UMyFileManager(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, m_RootGalleryPath("")
	, m_Concatenator("/")
	, m_ParentDirectoryPath("..")
	, m_CurrentDirectoryRelativePath(".")
	, m_PhotoViewerFullPath("")
{

}

void UMyFileManager::GoIntoCatalog(const FString& CatalogFullPath, const FString& CatalogName)
{
	if (CatalogFullPath != "")
	{
		if (CatalogName == m_CurrentDirectoryRelativePath)
		{
			m_PhotoViewerFullPath = CatalogFullPath;
			// show current catalog's content
			if (IsFileInsideExist(CatalogFullPath))
			{
				ShowPhotosFromDirectory(CatalogFullPath);
			}
			else
			{
//				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("NO images")));
				ShowNoPhotoWidget();
			}
		}
		else
		{
			FString catalogFullPath = CatalogFullPath;
			catalogFullPath.RemoveFromEnd(m_Concatenator);

			if (CatalogName == m_ParentDirectoryPath)
			{
				GoToParentDirectory(catalogFullPath);
			}
			else
			{
				FString currentFullPath = catalogFullPath + m_Concatenator + CatalogName;
				ShowInternalDirectories(currentFullPath);
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

	//	if file is NOT image remove it from array
	for (int32 i = 0; i < m_FileNames.Num(); ++i)
	{
		if (GetImageFormat(m_FileNames[i]) == EImageFormat::Invalid)
		{
			m_FileNames.RemoveAt(i);
			i--;
		}
	}

	return m_FileNames.Num();
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
			m_FileNames.Empty();
			FileMgr.FindFiles(m_FileNames, *currentPath, true, false);
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

void UMyFileManager::ReturnFromPhotoViewer()
{
	GoIntoCatalog(m_PhotoViewerFullPath, "");
}

UTexture2D* UMyFileManager::GetTexture(const FString& FileFullPath)
{
	UTexture2D* texture = nullptr;
//	bool isValid = false;

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(GetImageFormat(FileFullPath));

	//Load From File
	TArray<uint8> RawFileData;
	if (!FFileHelper::LoadFileToArray(RawFileData, *FileFullPath)) return NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//Create Texture2D!
	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
	{
		const TArray<uint8>* UncompressedBGRA = NULL;
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

			//Valid?
			if (!texture) return NULL;
			//~~~~~~~~~~~~~~

			////Out!
			//Width = ImageWrapper->GetWidth();
			//Height = ImageWrapper->GetHeight();

			//Copy!
			void* TextureData = texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
			texture->PlatformData->Mips[0].BulkData.Unlock();

			//Update!
			texture->UpdateResource();
		}
	}

	// Success!
//	isValid = true;
	return texture;
}

EImageFormat UMyFileManager::GetImageFormat(const FString& FileFullPath)
{
	EImageFormat imageFormat = EImageFormat::Invalid;
	FString extension = FPaths::GetExtension(FileFullPath);
	extension.ToLower();
	if (extension == "jpg" || extension == "jpeg")
	{
		imageFormat = EImageFormat::JPEG;
	}
	else if (extension == "png")
	{
		imageFormat = EImageFormat::PNG;
	}
	else if (extension == "bmp")
	{
		imageFormat = EImageFormat::BMP;
	}
	else if (extension == "ico")
	{
		imageFormat = EImageFormat::ICO;
	}
	else if (extension == "exr")
	{
		imageFormat = EImageFormat::EXR;
	}
	else if (extension == "icns")
	{
		imageFormat = EImageFormat::ICNS;
	}
	return imageFormat;
}

void UMyFileManager::ShowPhotosFromDirectory(const FString& CatalogFullPath)
{
	AAGHUD* HUD = Cast<AAGHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUD)
	{
		HUD->CreateWindow(EWidgeTType::PhotoViewer);

		HUD->ShowPhotos(CatalogFullPath, m_FileNames);
	}
}

void UMyFileManager::GoToParentDirectory(const FString& CurrentCatalogFullPath)
{
	FString parentPath = "";
	if (m_RootGalleryPath == CurrentCatalogFullPath)
	{
		//	prevent to go out of accessed catalog
		parentPath = CurrentCatalogFullPath;
	}
	else
	{
		//	get parent
		parentPath = FPaths::GetPath(CurrentCatalogFullPath);
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Catalog : %s"), *catalogFullPath));
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Parent : %s"), *parentPath));
	}
	GoIntoCatalog(parentPath, "");
}

void UMyFileManager::ShowInternalDirectories(const FString& CurrentCatalogFullPath)
{
	AAGHUD* HUD = Cast<AAGHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUD)
	{
		HUD->CreateWindow(EWidgeTType::CatalogViewer);
		HUD->ClearCatalogListWidget();

		if (IsCatalogInsideExist(CurrentCatalogFullPath))
		{
			for (int32 i = 0; i < m_ChildCatalogNames.Num(); ++i)
			{
				//	if catalog's name begins with "."
				if (m_ChildCatalogNames[i].Left(1) == ".")
				{
					m_ChildCatalogNames.RemoveAt(i);
				}
			}
			HUD->AddCatalogToCatalogListWidget(CurrentCatalogFullPath, m_ChildCatalogNames);
		}
		else
		{
			//	if within the catalog is no a sub-catalog
			HUD->AddCatalogToCatalogListWidget(CurrentCatalogFullPath, m_ParentDirectoryPath);
			HUD->AddCatalogToCatalogListWidget(CurrentCatalogFullPath, m_CurrentDirectoryRelativePath);
		}
	}
}

void UMyFileManager::ShowNoPhotoWidget()
{
	AAGHUD* HUD = Cast<AAGHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUD)
	{
		HUD->CreateWindow(EWidgeTType::NoPhoto);
	}
}