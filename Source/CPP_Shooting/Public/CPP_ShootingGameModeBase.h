// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Bullet.h"
#include "CPP_ShootingGameModeBase.generated.h"

// �Ѿ� ������ƮǮ�� ���� �Ӽ� ����
// �ʿ�Ӽ� : źâũ��, źâ(������ƮǮ), �Ѿ˰���
UCLASS()
class CPP_SHOOTING_API ACPP_ShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACPP_ShootingGameModeBase();

	virtual void BeginPlay() override;

	// �Ѿ� Ȱ��ȭ��Ű�� �Լ�
	void SetBulletActive(ABullet* bullet, bool isActive);
	
	// źâ�� �Ѿ��� �߰����ִ� �Լ�
	void AddBullet(ABullet* bullet);

	// �ʿ�Ӽ� : źâũ��, źâ(������ƮǮ), �Ѿ˰���
	UPROPERTY(EditDefaultsOnly, Category="Bullet")
	int bulletPoolSize;
	
	UPROPERTY(VisibleAnywhere, Category="Bullet")
	TArray<ABullet*> bulletPool;
	
	// ����
	UPROPERTY(EditDefaultsOnly, Category = "BulletClass")
	TSubclassOf<class ABullet> bulletFactory;
};
