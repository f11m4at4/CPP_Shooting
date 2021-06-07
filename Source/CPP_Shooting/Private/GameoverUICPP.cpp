// Fill out your copyright notice in the Description page of Project Settings.


#include "GameoverUICPP.h"
#include <Kismet/GameplayStatics.h>

void UGameoverUICPP::Restart()
{
	// ������ �����
	UGameplayStatics::OpenLevel(this, TEXT("Shooting"));
}

void UGameoverUICPP::Quit()
{
	// ������ �����Ѵ�.
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
