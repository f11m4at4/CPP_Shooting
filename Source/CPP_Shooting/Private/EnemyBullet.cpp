// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include <Components/SphereComponent.h>
#include <Kismet/GameplayStatics.h>
#include "CPP_ShootingGameModeBase.h"

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
	
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnTriggerEnter);
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

void AEnemyBullet::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �ε��� �༮�� Player �� �ƴ϶�� ó������ ����
	if (OtherActor->GetName().Contains(TEXT("Player")) == false)
	{
		return;
	}

	// ����ȿ�� �����ϱ�
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, GetActorTransform());

	// ���� ���� ���
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	// ���� ���� ���·� ��ȯ�ϰ� �ʹ�.
	gameMode->SetState(EGameState::Gameover);

	OtherActor->Destroy();
	Destroy();
}