// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyFileManager* UMyGameInstance::GetMyFileManager()
{
	if (!m_FileManager)
	{
		m_FileManager = NewObject<UMyFileManager>(this);
	}
	return m_FileManager;
}

UAndroidGateway* UMyGameInstance::GetAndroidGateway()
{
	if (!m_AndroidGateway)
	{
		m_AndroidGateway = NewObject<UAndroidGateway>(this);
	}
	return m_AndroidGateway;
}
