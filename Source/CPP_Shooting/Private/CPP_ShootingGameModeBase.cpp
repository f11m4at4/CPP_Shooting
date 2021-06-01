// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPP_ShootingGameModeBase.h"
#include "CPP_Shooting.h"

ACPP_ShootingGameModeBase::ACPP_ShootingGameModeBase()
{
	// Tick �Լ��� ��� ȣ��ǵ��� ����
	PrimaryActorTick.bCanEverTick = true;

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

void ACPP_ShootingGameModeBase::Tick(float DeltaSeconds)
{
	// �������� ����
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
	
	//// ���� ���¸� ����� ���� �ʹ�.
	/*const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGameState"), true);
	if (enumPtr)
	{
		PRINTLOG(TEXT("State : %s"), *enumPtr->GetNameStringByValue((uint8)mState));
	}*/
	PrintEnumData(mState);

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
	}
}

// �����ð� ��ٷȴٰ� ���¸� Playing ���� ��ȯ�ϰ� �ʹ�.
// -> Ready �ؽ�Ʈ ǥ���ϱ� log
// �ʿ�Ӽ� : (���ð�)�����ð�, ����ð�
void ACPP_ShootingGameModeBase::ReadyPage()
{
	//PRINTLOG(TEXT("READY STATE"));
	// �����ð� ��ٷȴٰ� ���¸� Playing ���� ��ȯ�ϰ� �ʹ�.
	// 1. �ð��� �귶���ϱ�
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 2. �����ð��� �����ϱ�
	// 	   ���� ����ð��� ���ð��� �ʰ��Ͽ��ٸ�
	if (currentTime > readyDelayTime)
	{
		// 3. ���¸� Playing ���� ��ȯ�ϰ� �ʹ�.
		mState = EGameState::Playing;
		currentTime = 0;
	}
}
// Start �ؽ�Ʈ ǥ���ϱ�
// Start �ؽ�Ʈ�� 2���� �������.
// ���� �����ϰ� �Ѵ�.
void ACPP_ShootingGameModeBase::PlayingPage()
{

}
// Gameover �޴�ǥ���ϱ�
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

void ACPP_ShootingGameModeBase::PrintEnumData_Implementation(EGameState value)
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGameState"), true);
	if (enumPtr)
	{
		PRINTLOG(TEXT("State : %s"), *enumPtr->GetNameStringByValue((uint8)value));
	}
}

ABullet* ACPP_ShootingGameModeBase::CreateBullet()
{
	// 1. �Ѿ˰��忡�� �Ѿ��� �����.
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, FVector::ZeroVector, FRotator::ZeroRotator, Param);

	return bullet;
}
