// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CatalogItemWidget.h"
#include "VerticalBox.h"
#include "CatalogListWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANDROIDGALLERY_API UCatalogListWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UCatalogListWidget(const FObjectInitializer & ObjectInitializer);

	void AddItem(const FString& CatalogFullPath, const FString& CatalogName);

	void ClearCatalogList();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<UCatalogItemWidget> m_UCatalogItemWidgetClass;

private:

	UPROPERTY()
	TArray<UCatalogItemWidget*> m_ItemArray;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* m_VerticalBox;
};
