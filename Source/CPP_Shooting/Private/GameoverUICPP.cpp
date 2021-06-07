// Fill out your copyright notice in the Description page of Project Settings.


#include "GameoverUICPP.h"
#include <Kismet/GameplayStatics.h>

void UGameoverUICPP::Restart()
{
	// 레벨을 재시작
	UGameplayStatics::OpenLevel(this, TEXT("Shooting"));
}

void UGameoverUICPP::Quit()
{
	// 게임을 종료한다.
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
