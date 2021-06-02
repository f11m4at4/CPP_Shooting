// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPP_ShootingGameModeBase.h"
#include "CPP_Shooting.h"
#include "Enemy.h"
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>

ACPP_ShootingGameModeBase::ACPP_ShootingGameModeBase()
{
	// Tick 함수가 계속 호출되도록 설정
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = NULL;

	// 탄창 크기 정해주자
	bulletPoolSize = 10;
}

void ACPP_ShootingGameModeBase::InitGameState()
{
	Super::InitGameState();

	// 화면에 Enemy 가 있으면 다 제거해준다.
	/*
	TArray<AActor*> objs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), objs);
	for (auto obj:objs)
	{
		AEnemy* enemy = Cast<AEnemy>(obj);
		enemy->Destroy();
	}
	*/
	for (TActorIterator<AEnemy> it( GetWorld() ) ; it; ++it )
	{
		it->Destroy();
	}

	// 화면에 총알이 있으면 다 풀에 넣어준다.
	// Player 가 없으면 만들어주자.
	// 게임의 상태를 Ready 로 설정해 주자.
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
	
	//// 현재 상태를 출력해 보고 싶다.
	/*const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGameState"), true);
	if (enumPtr)
	{
		PRINTLOG(TEXT("State : %s"), *enumPtr->GetNameStringByValue((uint8)mState));
	}*/
	//PrintEnumData(mState);

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

// 일정시간 기다렸다가 상태를 Playing 으로 전환하고 싶다.
// -> Ready 텍스트 표현하기 log
// 필요속성 : (대기시간)일정시간, 경과시간
void ACPP_ShootingGameModeBase::ReadyPage()
{
	//PRINTLOG(TEXT("READY STATE"));
	// 일정시간 기다렸다가 상태를 Playing 으로 전환하고 싶다.
	// 1. 시간이 흘렀으니까
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 2. 일정시간이 됐으니까
	// 	   만약 경과시간이 대기시간을 초과하였다면
	if (currentTime > readyDelayTime)
	{
		// 3. 상태를 Playing 으로 전환하고 싶다.
		mState = EGameState::Playing;
		currentTime = 0;
	}
}
// Start 텍스트 표현하기
// Start 텍스트는 2초후 사라진다.
// 게임 동작하게 한다.
void ACPP_ShootingGameModeBase::PlayingPage()
{

}
// Gameover 메뉴표현하기
// R 키를 누르면 다시 시작 시키기
void ACPP_ShootingGameModeBase::GameoverPage()
{
	// R 키를 입력 받기
	// 1. PlayerController 가져오기
	APlayerController* myController = GetWorld()->GetFirstPlayerController();
	//APlayerController* myController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// 2. 키입력 처리 -> R키를 눌렀다면
	// myController 가 있고 R 키를 눌렀다면
	if (myController && myController->WasInputKeyJustPressed(EKeys::R))
	{
		PRINTLOG(TEXT("R Key Pressed!!!!!!!!!!!!"));
		ResetLevel();
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
	// 1. 총알공장에서 총알을 만든다.
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, FVector::ZeroVector, FRotator::ZeroRotator, Param);

	return bullet;
}
