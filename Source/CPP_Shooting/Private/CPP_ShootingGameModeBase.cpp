// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPP_ShootingGameModeBase.h"

ACPP_ShootingGameModeBase::ACPP_ShootingGameModeBase()
{
	// Tick 함수가 계속 호출되도록 설정
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = NULL;

	// 탄창 크기 정해주자
	bulletPoolSize = 10;
}

void ACPP_ShootingGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 탄창에 총알 만들어서 넣자
	for (int32 i = 0; i<bulletPoolSize; ++i)
	{
		ABullet* bullet = CreateBullet();

		AddBullet(bullet);
	}
}

void ACPP_ShootingGameModeBase::Tick(float DeltaSeconds)
{
	// 상태제어 설계
	//if (mState == EGameState::Ready)
	//{
	//	// to do
	//}
	//else if (mState == EGameState::Playing)
	//{
	//	// to do
	//}
	//else if (mState == EGameState::Gameover)
	//{
	//	// to do
	//}
	//else
	//{
	//	// to do
	//}
	switch (mState)
	{
	case EGameState::Ready:
		ReadyPage();
		break;
	case EGameState::Playing:
		PlayingPage();
		break;
	case EGameState::Gameover:
		GameoverPage();
		break;
	default:
	}
}

// 일정시간 기다렸다가 상태를 Playing 으로 전환하고 싶다.
// -> Ready 텍스트 표현하기
void ACPP_ShootingGameModeBase::ReadyPage()
{

}
// Start 텍스트 표현하기
// Start 텍스트는 2초후 사라진다.
// 게임 동작하게 한다.
void ACPP_ShootingGameModeBase::PlayingPage()
{

}
// Gameover 메뉴표현하기
void ACPP_ShootingGameModeBase::GameoverPage()
{

}

void ACPP_ShootingGameModeBase::SetBulletActive(ABullet* bullet, bool isActive)
{
	bullet->SetActorHiddenInGame(!isActive);
	bullet->SetActorEnableCollision(isActive);
	bullet->SetActorTickEnabled(isActive);
}

void ACPP_ShootingGameModeBase::AddBullet(ABullet* bullet)
{
	// 2. 탄창에 총알을 넣는다.
	bulletPool.AddUnique(bullet);

	// 3. 총알을 비활성화 시킨다.
	SetBulletActive(bullet, false);
}

ABullet* ACPP_ShootingGameModeBase::GetBullet()
{
	// 탄창에서 총알을 하나 빼오고 싶다.
	/*
	for (int32 i = 0;i<bulletPoolSize;++i)
	{
		// 안보인다. -> 비활성화
		if (bulletPool[i]->IsHidden())
		{
			ABullet* bullet = bulletPool[i];
			bulletPool.RemoveAt(0);
			return bullet;
		}
	}*/
	/*
	// 배열에 값이 하나 미만이라면 null 을 반환
	if (bulletPool.Num() < 1)
	{
		return nullptr;
	}

	// 1. 풀에서 총알을 하나 빼오기
	ABullet* bullet = bulletPool[0];
	// 2. 탄창에서 빼온 총알 없애기
	bulletPool.RemoveAt(0);
	// -> RemoveAt
	// 3. 총알을 반환해주기
	return bullet;
	*/
	ABullet* bullet = bulletPool.Pop();
	return bullet;
}

ABullet* ACPP_ShootingGameModeBase::CreateBullet()
{
	// 1. 총알공장에서 총알을 만든다.
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, FVector::ZeroVector, FRotator::ZeroRotator, Param);

	return bullet;
}
