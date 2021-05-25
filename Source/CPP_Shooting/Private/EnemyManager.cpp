// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// - 일정시간에 한번씩 "적 생성" 로그를 찍고 싶다.
	// 1. 시간이 흘렀으니까
	currentTime += DeltaTime;
	// 2. 만약 경과시간이 생성시간을 초과했다면
	// 3. 로그찍기
	PRINTLOG(TEXT("적 생성"));
}

