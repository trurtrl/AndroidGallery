// Fill out your copyright notice in the Description page of Project Settings.


#include "NoPhotoWidget.h"
#include "MyFileManager.h"
#include "MyGameInstance.h"


UNoPhotoWidget::UNoPhotoWidget(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, m_ButtonBack(nullptr)
{

}

void UNoPhotoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (m_ButtonBack && !m_ButtonBack->OnReleased.IsBound())
	{
		m_ButtonBack->OnReleased.AddDynamic(this, &UNoPhotoWidget::ButtonBackClicked);
	}
}

void UNoPhotoWidget::ButtonBackClicked()
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (GI)
	{
		GI->GetMyFileManager()->ReturnFromPhotoViewer();
	}
}