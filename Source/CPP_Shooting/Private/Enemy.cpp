// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "PlayerCPP.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������Ʈ ���� ���̱�
	// 1. Box Collider
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollier"));
	RootComponent = boxComp;
	// 2. �ܰ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
		
	TArray<AActor*> objs;
	// �¾�� Ÿ���� ã�� ����
	// -> UE4 ���� ����� �ִ� ���� ã��
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCPP::StaticClass(), objs);

	// for ���� objs �� �˻�
	/*for (int i=0;i<objs.Num();i++)
	{
		target = objs[0];
	}*/
	for (AActor* actor : objs)
	{
		target = actor;
	}
	dir = FVector::DownVector;
	// ���� target �� ���� ����� ��� �ִٸ� �̸��� ����غ���
	if (target != nullptr)
	{
		// 1. ������ �ʿ��ϴ�.
		// dir = target - me
		
		// dir ���� �� target ������ Ÿ�������� �׷��� ������
		// �׸��� target �� ��ȿ�ϸ�
		if (target && IsValid(target))
		{
			// ������ Ÿ��������
			dir = target->GetActorLocation() - GetActorLocation();
		}
		dir.Normalize();
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector vel = dir * speed;

	FVector P0 = GetActorLocation();
	FVector P = P0 + vel * DeltaTime;
	// 2. ��ġ�� �����ϰ� �ʹ�. -> �̵��ϰ�ʹ�.
	SetActorLocation(P);
}

// �ٸ� ��ü�� ������ �� ȣ��Ǵ� �̺�Ʈ �Լ�
// ���� �װ� ���� �װ� ����
void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	OtherActor->Destroy();
	Destroy();
}

