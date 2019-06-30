// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "NoPhotoWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANDROIDGALLERY_API UNoPhotoWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UNoPhotoWidget(const FObjectInitializer & ObjectInitializer);

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(meta = (BindWidget))
	UButton* m_ButtonBack;

	UFUNCTION()
	void ButtonBackClicked();
	
};
