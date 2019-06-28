// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Runtime/Core/Public/Delegates/DelegateSignatureImpl.inl"
#include "CatalogItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANDROIDGALLERY_API UCatalogItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetName(const FString& CatalogFullPath, const FString& CatalogName);

private:

	UPROPERTY(meta = (BindWidget))
	UButton* m_Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* m_TextBlock;

	FString m_CatalogFullPath;
	FString m_CatalogName;

	UFUNCTION()
	void ButtonClicked();

};
