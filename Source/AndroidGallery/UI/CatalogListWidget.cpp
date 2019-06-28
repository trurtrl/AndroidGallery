// Fill out your copyright notice in the Description page of Project Settings.


#include "CatalogListWidget.h"
#include "UObject/ConstructorHelpers.h"


UCatalogListWidget::UCatalogListWidget(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UCatalogItemWidget>UCatalogItemWidgetClassFinder(TEXT("WidgetBlueprint'/Game/WBP_CatalogItem.WBP_CatalogItem_C'"));
	if (UCatalogItemWidgetClassFinder.Succeeded())
	{
		m_UCatalogItemWidgetClass = UCatalogItemWidgetClassFinder.Class;
	}
}

void UCatalogListWidget::AddItem(const FString& CatalogPath, const FString& CatalogName)
{
	if (m_VerticalBox)
	{
//		UCatalogItemWidget* item = NewObject<UCatalogItemWidget>(this, UCatalogItemWidget::StaticClass());

		UCatalogItemWidget* item = CreateWidget<UCatalogItemWidget>(GetWorld(), m_UCatalogItemWidgetClass);
		m_ItemArray.Add(item);

		item->SetName(CatalogPath, CatalogName);
		m_VerticalBox->AddChild(item);
	}
}

void UCatalogListWidget::ClearCatalogList()
{
	m_VerticalBox->ClearChildren();
	m_ItemArray.Empty();
}