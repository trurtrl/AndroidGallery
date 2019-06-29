// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UserWidget.h"
#include "MainWidget.h"
#include "CatalogListWidget.h"
#include "PhotoViewerWidget.h"
#include "AGHUD.generated.h"


enum class EWidgeTType : uint8
{
	None,
	Main,
	CatalogViewer,
	PhotoViewer
};

/**
 * 
 */
UCLASS()
class ANDROIDGALLERY_API AAGHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AAGHUD();

	virtual void BeginPlay() override;

	void CreateWindow(EWidgeTType Type);

	//	CatalogListWidget
	void AddCatalogToCatalogListWidget(const FString& Path, const TArray<FString>& Catalogs);
	void AddCatalogToCatalogListWidget(const FString& Path, const FString& Catalog);

	void ClearCatalogListWidget();

	//	PhotoViewerWidget
	void ShowPhotos(const FString& Path, const TArray<FString>& FileNameArray);


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<UMainWidget> m_UMainWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<UCatalogListWidget> m_UCatalogListWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<UPhotoViewerWidget> m_UPhotoViewerWidgetClass;


private:

	EWidgeTType m_CurrentWidgetType;

	UPROPERTY()
	UUserWidget* m_CurrentWidget;

};
