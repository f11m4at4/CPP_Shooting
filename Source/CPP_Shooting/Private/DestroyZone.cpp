// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyZone.h"
#include <Components/StaticMeshComponent.h>
#include "PlayerCPP.h"


// Sets default values
ADestroyZone::ADestroyZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 추가
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = meshComp;
}

// Called when the game starts or when spawned
void ADestroyZone::BeginPlay()
{
	Super::BeginPlay();
	
	meshComp->OnComponentHit.AddDynamic(this, &ADestroyZone::OnCollisionEnter);
}

// Called every frame
void ADestroyZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyZone::OnCollisionEnter(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 만약 Player 라면 처리 안한다.
	APlayerCPP* player = Cast<APlayerCPP>(OtherActor);
	if (player != nullptr)
	{
		return;
	}

	// 부딪힌 녀석 제거
	OtherActor->Destroy();
}

