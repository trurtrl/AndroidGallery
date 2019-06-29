// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANDROIDGALLERY_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetTexture(UTexture2D* Texture);

private:

	UPROPERTY(meta = (BindWidget))
	UImage* m_Image;
};
