// Fill out your copyright notice in the Description page of Project Settings.


#include "PhotoViewerWidget.h"
#include "MyFileManager.h"
#include "MyGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"


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

	if (m_ButtonBack && !m_ButtonBack->OnReleased.IsBound())
	{
		m_ButtonBack->OnReleased.AddDynamic(this, &UPhotoViewerWidget::ButtonBackClicked);
	}

	if (m_ScrollBox && !m_ScrollBox->OnUserScrolled.IsBound())
	{
		m_ScrollBox->OnUserScrolled.AddDynamic(this, &UPhotoViewerWidget::OnUserScrolledHandle);
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


void UPhotoViewerWidget::ShowPhotos(const FString& Path, const TArray<FString>& FileNameArray)
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (GI && m_UItemWidgetClass)
	{
		m_CatalogPath = Path;
		m_FileNameArray = FileNameArray;

		int32 photoToShowNum = FMath::Min(m_ItemToSpawnNum, FileNameArray.Num());

		for (int32 i = 0; i < photoToShowNum; i++)
		{
			UItemWidget* item = CreateWidget<UItemWidget>(GetWorld(), m_UItemWidgetClass);
			FString fileFulPath = Path + GI->GetMyFileManager()->GetConcatenator() + FileNameArray[i];
			item->SetTexture(GI->GetMyFileManager()->GetTexture(fileFulPath));
			m_ItemArray.Add(item);
			m_ScrollBox->AddChild(item);
		}
	}
}

void UPhotoViewerWidget::OnUserScrolledHandle(float Offset)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Magenta, FString::Printf(TEXT("Offset %f"), Offset));
}