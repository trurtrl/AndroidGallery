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
	default:
		break;
	}

	if (m_CurrentWidget) {
		m_CurrentWidget->RemoveFromViewport();
	}

	m_CurrentWidget = newWidget;
	if (m_CurrentWidget)
	{
		m_CurrentWidget->AddToViewport();
	}
}
