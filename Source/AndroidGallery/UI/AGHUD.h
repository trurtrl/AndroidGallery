// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UserWidget.h"
#include "MainWidget.h"
#include "AGHUD.generated.h"


enum class EWidgeTType : uint8
{
	None,
	Main,
	Viewer
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


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<UMainWidget> m_UMainWidgetClass;


private:

	EWidgeTType m_CurrentWidgetType;

	UPROPERTY()
	UUserWidget* m_CurrentWidget;

};
