// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Bullet.h"
#include "CPP_ShootingGameModeBase.generated.h"

// 총알 오브젝트풀을 위한 속성 선언
// 필요속성 : 탄창크기, 탄창(오브젝트풀), 총알공장
UCLASS()
class CPP_SHOOTING_API ACPP_ShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACPP_ShootingGameModeBase();

	virtual void BeginPlay() override;

	// 총알 활성화시키는 함수
	void SetBulletActive(ABullet* bullet, bool isActive);
	
	// 탄창에 총알을 추가해주는 함수
	void AddBullet(ABullet* bullet);

	// 필요속성 : 탄창크기, 탄창(오브젝트풀), 총알공장
	UPROPERTY(EditDefaultsOnly, Category="Bullet")
	int bulletPoolSize;
	
	UPROPERTY(VisibleAnywhere, Category="Bullet")
	TArray<ABullet*> bulletPool;
	
	// 공장
	UPROPERTY(EditDefaultsOnly, Category = "BulletClass")
	TSubclassOf<class ABullet> bulletFactory;
};
