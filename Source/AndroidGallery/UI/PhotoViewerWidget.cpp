// Fill out your copyright notice in the Description page of Project Settings.


#include "PhotoViewerWidget.h"
#include "MyFileManager.h"
#include "MyGameInstance.h"
#include "UObject/ConstructorHelpers.h"


UPhotoViewerWidget::UPhotoViewerWidget(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, m_ItemToSpawnNum(5)
{
	static ConstructorHelpers::FClassFinder<UItemWidget>UItemWidgetClassFinder(TEXT("WidgetBlueprint'/Game/WBP_Item.WBP_Item_C'"));
	if (UItemWidgetClassFinder.Succeeded())
	{
		m_UItemWidgetClass = UItemWidgetClassFinder.Class;
	}
}

void UPhotoViewerWidget::NativeConstruct()
{
	Super::NativeConstruct();

//	m_ItemArray.Init(NewObject<UImage>(), 3);

	if (m_ButtonBack && !m_ButtonBack->OnReleased.IsBound())
	{
		m_ButtonBack->OnReleased.AddDynamic(this, &UPhotoViewerWidget::ButtonBackClicked);
	}
}

void UPhotoViewerWidget::ButtonBackClicked()
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (GI)
	{
		GI->GetMyFileManager()->ReturnFromPhotoViewer();
	}
}

void UPhotoViewerWidget::SetPhotoTextures(const TArray<UTexture2D*>& TextureArray)
{
	//m_ScrollBox->ClearChildren();
	if (m_UItemWidgetClass)
	{
		int32 photoToShowNum = FMath::Min(m_ItemToSpawnNum, TextureArray.Num());

		for (int32 i = 0; i < photoToShowNum; i++)
		{
			UItemWidget* item = CreateWidget<UItemWidget>(GetWorld(), m_UItemWidgetClass);
			item->SetTexture(TextureArray[i]);
			m_ItemArray.Add(item);
			m_ScrollBox->AddChild(item);
		}
	}
}
