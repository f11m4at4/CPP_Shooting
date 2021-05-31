// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPP_ShootingGameModeBase.h"

ACPP_ShootingGameModeBase::ACPP_ShootingGameModeBase()
{
	DefaultPawnClass = NULL;

	// źâ ũ�� ��������
	bulletPoolSize = 10;
}

void ACPP_ShootingGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// źâ�� �Ѿ� ���� ����
	for (int32 i = 0; i<bulletPoolSize; ++i)
	{
		// 1. �Ѿ˰��忡�� �Ѿ��� �����.
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
	// 2. źâ�� �Ѿ��� �ִ´�.
	bulletPool.AddUnique(bullet);

	// 3. �Ѿ��� ��Ȱ��ȭ ��Ų��.
	SetBulletActive(bullet, false);
}
