// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include <Components/SphereComponent.h>

// Sets default values
AEnemyBullet::AEnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������Ʈ ���� ���̱�
	// 1. Box Collider
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollier"));
	RootComponent = sphereComp;
	// 2. �ܰ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(sphereComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 1. ������ �ʿ��ϴ�.
	//FVector vel = GetActorForwardVector() * speed;
	FVector vel = FVector::DownVector * speed;

	FVector P0 = GetActorLocation();
	FVector P = P0 + vel * DeltaTime;
	// 2. ��ġ�� �����ϰ� �ʹ�. -> �̵��ϰ�ʹ�.
	SetActorLocation(P, true);
}

