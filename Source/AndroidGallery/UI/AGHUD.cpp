// Fill out your copyright notice in the Description page of Project Settings.


#include "AGHUD.h"
#include "UObject/ConstructorHelpers.h"


AAGHUD::AAGHUD()
{
	static ConstructorHelpers::FClassFinder<UMainWidget> UMainWidgetClassFinder(TEXT("/Game/WBP_Main.WBP_Main_C"));
	if (UMainWidgetClassFinder.Succeeded())
	{
		m_UMainWidgetClass = UMainWidgetClassFinder.Class;
	}
	static ConstructorHelpers::FClassFinder<UCatalogListWidget> UCatalogListWidgetClassFinder(TEXT("WidgetBlueprint'/Game/WBP_CatalogList.WBP_CatalogList_C'"));
	if (UCatalogListWidgetClassFinder.Succeeded())
	{
		m_UCatalogListWidgetClass = UCatalogListWidgetClassFinder.Class;
	}
	static ConstructorHelpers::FClassFinder<UPhotoViewerWidget> UPhotoViewerWidgetClassFinder(TEXT("WidgetBlueprint'/Game/WBP_PhotoViewer.WBP_PhotoViewer_C'"));
	if (UPhotoViewerWidgetClassFinder.Succeeded())
	{
		m_UPhotoViewerWidgetClass = UPhotoViewerWidgetClassFinder.Class;
	}
}

void AAGHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateWindow(EWidgeTType::Main);
}

void AAGHUD::CreateWindow(EWidgeTType Type)
{
	if (m_CurrentWidgetType == Type)
	{
		return;
	}

	UUserWidget* newWidget = nullptr;
	switch (Type)
	{
	case EWidgeTType::None:
		break;
	case EWidgeTType::Main:
	{
		if (m_UMainWidgetClass) {
			newWidget = CreateWidget<UMainWidget>(GetWorld(), m_UMainWidgetClass);
		}
	}
	break;
	case EWidgeTType::CatalogViewer:
	{
		if (m_UCatalogListWidgetClass) {
			newWidget = CreateWidget<UCatalogListWidget>(GetWorld(), m_UCatalogListWidgetClass);
		}
	}
	break;
	case EWidgeTType::PhotoViewer:
	{
		if (m_UPhotoViewerWidgetClass) {
			newWidget = CreateWidget<UPhotoViewerWidget>(GetWorld(), m_UPhotoViewerWidgetClass);
		}
	}
	break;
	default:
		break;
	}

	if (m_CurrentWidget) {
		m_CurrentWidget->RemoveFromViewport();
	}

	m_CurrentWidget = newWidget;
	m_CurrentWidgetType = Type;
	if (m_CurrentWidget)
	{
		m_CurrentWidget->AddToViewport();
	}
}

void AAGHUD::AddCatalogToCatalogListWidget(const FString& Path, const TArray<FString>& Catalogs)
{
	UCatalogListWidget* catalogListWidget = Cast<UCatalogListWidget>(m_CurrentWidget);
	if (catalogListWidget)
	{
		//	add "go to 1 level up"
		catalogListWidget->AddItem(Path, "..");

		//	add "go into this catalog"
		catalogListWidget->AddItem(Path, ".");

		//	add catalogs
		for (FString catalog : Catalogs)
		{
			catalogListWidget->AddItem(Path, catalog);
		}
	}
}

void AAGHUD::AddCatalogToCatalogListWidget(const FString& Path, const FString& Catalog)
{
	UCatalogListWidget* catalogListWidget = Cast<UCatalogListWidget>(m_CurrentWidget);
	if (catalogListWidget)
	{
		catalogListWidget->AddItem(Path, Catalog);
	}
}

void AAGHUD::ClearCatalogListWidget()
{
	UCatalogListWidget* catalogListWidget = Cast<UCatalogListWidget>(m_CurrentWidget);
	if (catalogListWidget)
	{
		catalogListWidget->ClearCatalogList();
	}
}


void AAGHUD::ShowPhotos(const FString& Path, const TArray<FString>& FileNameArray)
{
	UPhotoViewerWidget* photoViewer = Cast<UPhotoViewerWidget>(m_CurrentWidget);
	if (photoViewer)
	{
		photoViewer->ShowPhotos(Path, FileNameArray);
	}
}