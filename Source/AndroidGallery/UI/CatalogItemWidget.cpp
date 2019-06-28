// Fill out your copyright notice in the Description page of Project Settings.


#include "CatalogItemWidget.h"
#include "MyGameInstance.h"


void UCatalogItemWidget::SetName(const FString& CatalogFullPath, const FString& CatalogName)
{
	if (m_TextBlock)
	{
		m_TextBlock->SetText(FText::FromString(CatalogName));
	}

	if (m_Button && !m_Button->OnClicked.IsBound())
	{
		m_Button->OnClicked.AddDynamic(this, &UCatalogItemWidget::ButtonClicked);
	}

	m_CatalogFullPath = CatalogFullPath;
	m_CatalogName = CatalogName;
}

void UCatalogItemWidget::ButtonClicked()
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (GI)
	{
		GI->GetMyFileManager()->GoIntoCatalog(m_CatalogFullPath, m_CatalogName);
	}
}
