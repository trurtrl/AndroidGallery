// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "AndroGallery/Public/AndroidGateway.h"
#include "AndroGallery.h"
#include "MyGameInstance.h"


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
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (GI)
	{
		UAndroidGateway* androidGateway = GI->GetAndroidGateway();
		if (!androidGateway->OnExternalStoragePath.IsBound())
		{
			androidGateway->OnExternalStoragePath.AddDynamic(this, &UMainWidget::OnExternalStoragePathHandle);
		}

		androidGateway->AskGalleryRootPath();
	}
}

void UMainWidget::OnExternalStoragePathHandle(const FString Path)
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (GI)
	{
		GI->GetMyFileManager()->GoIntoCatalog(Path);
	}
}