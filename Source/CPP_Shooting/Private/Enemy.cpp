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

	// 컴포넌트 만들어서 붙이기
	// 1. Box Collider
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollier"));
	RootComponent = boxComp;
	// 2. 외관
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
		
	TArray<AActor*> objs;
	// 태어날때 타겟을 찾아 놓자
	// -> UE4 에서 월드상에 있는 액터 찾기
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCPP::StaticClass(), objs);

	// for 문을 objs 를 검색
	/*for (int i=0;i<objs.Num();i++)
	{
		target = objs[0];
	}*/
	for (AActor* actor : objs)
	{
		target = actor;
	}
	dir = FVector::DownVector;
	// 만약 target 에 값이 제대로 들어 있다면 이름을 출력해보자
	if (target != nullptr)
	{
		// 1. 방향이 필요하다.
		// dir = target - me
		
		// dir 구할 때 target 있으면 타겟쪽으로 그렇지 않으면
		// 그리고 target 이 유효하면
		if (target && IsValid(target))
		{
			// 방향을 타겟쪽으로
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
	// 2. 위치를 지정하고 싶다. -> 이동하고싶다.
	SetActorLocation(P);
}

// 다른 물체와 겹쳤을 때 호출되는 이벤트 함수
// 갸도 죽고 나도 죽게 하자
void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	OtherActor->Destroy();
	Destroy();
}

