// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyFileManager.h"
#include "AndroGallery/Public/AndroidGateway.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ANDROIDGALLERY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:

	UMyFileManager* GetMyFileManager();
	UAndroidGateway* GetAndroidGateway();

private:

	UPROPERTY()
	UMyFileManager* m_FileManager;

	UPROPERTY()
	UAndroidGateway* m_AndroidGateway;

};
