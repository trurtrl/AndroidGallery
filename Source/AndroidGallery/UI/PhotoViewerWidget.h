// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NoPhotoWidget.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "ItemWidget.h"
#include "PhotoViewerWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANDROIDGALLERY_API UPhotoViewerWidget : public UNoPhotoWidget
{
	GENERATED_BODY()
	
public:

	UPhotoViewerWidget(const FObjectInitializer & ObjectInitializer);

	virtual void NativeConstruct() override;

	void ShowPhotos(const FString& Path, const TArray<FString>& FileNameArray);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemWidget> m_UItemWidgetClass;

private:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* m_ScrollBox;

	UPROPERTY()
	TArray<UItemWidget*> m_ItemArray;

//	int32 m_ItemToSpawnNum;

	UFUNCTION()
	void OnUserScrolledHandle(float Offset);

	FString	m_CatalogPath;
	TArray<FString> m_FileNameArray;
};
