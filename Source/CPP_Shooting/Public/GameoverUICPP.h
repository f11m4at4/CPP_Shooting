// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameoverUICPP.generated.h"

/**
 * 
 */
UCLASS()
class CPP_SHOOTING_API UGameoverUICPP : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Blueprint ���� �ش� �Լ��� ȣ�� �� �� �ֵ��� ����
	UFUNCTION(BlueprintCallable)
	void Restart();

	UFUNCTION(BlueprintCallable)
	void Quit();
};
