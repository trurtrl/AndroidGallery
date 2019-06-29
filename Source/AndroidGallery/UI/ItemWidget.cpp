// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

void UItemWidget::SetTexture(UTexture2D* Texture)
{
	m_Image->SetBrushFromTexture(Texture);
}