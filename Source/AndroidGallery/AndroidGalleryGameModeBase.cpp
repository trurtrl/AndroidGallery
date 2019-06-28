// Fill out your copyright notice in the Description page of Project Settings.


#include "AndroidGalleryGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"

void AAndroidGalleryGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController());
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}