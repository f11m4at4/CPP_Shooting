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
		ABullet* bullet = CreateBullet();

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

ABullet* ACPP_ShootingGameModeBase::GetBullet()
{
	// źâ���� �Ѿ��� �ϳ� ������ �ʹ�.
	/*
	for (int32 i = 0;i<bulletPoolSize;++i)
	{
		// �Ⱥ��δ�. -> ��Ȱ��ȭ
		if (bulletPool[i]->IsHidden())
		{
			ABullet* bullet = bulletPool[i];
			bulletPool.RemoveAt(0);
			return bullet;
		}
	}*/
	/*
	// �迭�� ���� �ϳ� �̸��̶�� null �� ��ȯ
	if (bulletPool.Num() < 1)
	{
		return nullptr;
	}

	// 1. Ǯ���� �Ѿ��� �ϳ� ������
	ABullet* bullet = bulletPool[0];
	// 2. źâ���� ���� �Ѿ� ���ֱ�
	bulletPool.RemoveAt(0);
	// -> RemoveAt
	// 3. �Ѿ��� ��ȯ���ֱ�
	return bullet;
	*/
	ABullet* bullet = bulletPool.Pop();
	return bullet;
}

ABullet* ACPP_ShootingGameModeBase::CreateBullet()
{
	// 1. �Ѿ˰��忡�� �Ѿ��� �����.
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, FVector::ZeroVector, FRotator::ZeroRotator, Param);

	return bullet;
}
