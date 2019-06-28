// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Engine/Engine.h"
#include "AndroGallery.h"


UMainWidget::UMainWidget(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, m_AndroidGateway(nullptr)
	, m_FileManager(nullptr)
{

}

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (m_ButtonGetPics && !m_ButtonGetPics->OnReleased.IsBound())
	{
		m_ButtonGetPics->OnReleased.AddDynamic(this, &UMainWidget::ButtonGetPicsClicked);
	}

	m_AndroidGateway = NewObject<UAndroidGateway>(this);
	m_FileManager = NewObject<UMyFileManager>(this);
}

void UMainWidget::ButtonGetPicsClicked()
{
	if (!m_AndroidGateway->OnExternalStoragePath.IsBound())
	{
		m_AndroidGateway->OnExternalStoragePath.AddDynamic(this, &UMainWidget::OnExternalStoragePathHandle);
	}

	m_AndroidGateway->AskGalleryRootPath();
}

void UMainWidget::OnExternalStoragePathHandle(const FString Path)
{
	if (Path != "" && m_FileManager)
	{
		bool catalogIsEmpty = true;
		if (m_FileManager->IsCatalogInsideExist(Path))
		{
			TArray<FString> content = m_FileManager->GetCatalogNames();
			for (FString name : content)
			{
				if (name.Left(1) != ".")
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Catalog : %s"), *name));
				}
			}
			catalogIsEmpty = false;
		}
		if (m_FileManager->IsFileInsideExist(Path))
		{
			TArray<FString> content = m_FileManager->GetFileNames();
			for (FString name : content)
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
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Path : %s"), *Path));
}