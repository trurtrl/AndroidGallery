// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Engine/Engine.h"
#include "AndroGallery.h"


void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (m_ButtonGetPics && !m_ButtonGetPics->OnReleased.IsBound())
	{
		m_ButtonGetPics->OnReleased.AddDynamic(this, &UMainWidget::ButtonGetPicsClicked);
	}

	m_AndroidGateway = NewObject<UAndroidGateway>(this);
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
	if (Path != "")
	{
		//	handle path
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Path : %s"), *Path));
}