// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANDROIDGALLERY_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//UMainWidget(const FObjectInitializer & ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* m_ButtonGetPics;


private:

	UFUNCTION()
	void ButtonGetPicsClicked();
	
};
