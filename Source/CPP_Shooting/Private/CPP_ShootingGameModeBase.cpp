// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPP_ShootingGameModeBase.h"

ACPP_ShootingGameModeBase::ACPP_ShootingGameModeBase()
{
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
		// 1. 총알공장에서 총알을 만든다.
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		auto bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, FVector::ZeroVector, FRotator::ZeroRotator, Param);

		AddBullet(bullet);
	}
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
