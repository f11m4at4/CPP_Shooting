// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Bullet.h"
#include "CPP_ShootingGameModeBase.generated.h"

// 총알 오브젝트풀을 위한 속성 선언
// 필요속성 : 탄창크기, 탄창(오브젝트풀), 총알공장

// 게임의 상태제어
// -> Ready, Playing, Gameover
// 열거형
UENUM(BlueprintType)
enum class EGameState : uint8
{
	Ready UMETA(DisplayName = "READY_STATE"),
	Playing UMETA(DisplayName = "PLAYING_STATE"),
	Gameover UMETA(DisplayName = "GAMEOVER_STATE")
};


UCLASS()
class CPP_SHOOTING_API ACPP_ShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACPP_ShootingGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void ReadyPage();
	void PlayingPage();
	void GameoverPage();


	// 총알 활성화시키는 함수
	void SetBulletActive(ABullet* bullet, bool isActive);
	
	// 탄창에 총알을 추가해주는 함수
	void AddBullet(ABullet* bullet);

	// 탄창(풀)에서 총알을 하나 빼오기
	ABullet* GetBullet();

private:
	ABullet* CreateBullet();

	// 상태변수
	// -> Blueprint 에 속성(변수) 노출시키고 싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta=(AllowPrivateAccess = true))
	EGameState mState = EGameState::Ready;	

	// 필요속성 : 탄창크기, 탄창(오브젝트풀), 총알공장
	UPROPERTY(EditDefaultsOnly, Category = "Bullet", meta = (AllowPrivateAccess = true))
	int bulletPoolSize;

	UPROPERTY(VisibleAnywhere, Category = "Bullet", meta = (AllowPrivateAccess = true))
	TArray<ABullet*> bulletPool;

	// 공장
	UPROPERTY(EditDefaultsOnly, Category = "BulletClass", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ABullet> bulletFactory;
};
