// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Engine/Engine.h"
#include "AndroGallery.h"
#include "AndroGallery/Public/AndroidGateway.h"


void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (m_ButtonGetPics && !m_ButtonGetPics->OnReleased.IsBound())
	{
		m_ButtonGetPics->OnReleased.AddDynamic(this, &UMainWidget::ButtonGetPicsClicked);
	}
}

void UMainWidget::ButtonGetPicsClicked()
{
	FString path = "";

	FAndroidGatewayPtr gatewayPtr = FAndroGalleryInterface::Get().GetGateway();
	if (gatewayPtr.IsValid())
	{
		if (!gatewayPtr.Get()->OnExternalStoragePath.IsBound())
		{
			gatewayPtr.Get()->OnExternalStoragePath.AddDynamic(this, &UMainWidget::OnExternalStoragePathHandle);
		}
		gatewayPtr.Get()->AskGalleryRootPath();
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Path : %s"), *path));
}

void UMainWidget::OnExternalStoragePathHandle(const FString Path)
{
	if (Path != "")
	{
		//	handle path
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Path : %s"), *Path));
}