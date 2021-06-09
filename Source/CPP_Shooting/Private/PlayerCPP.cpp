// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Materials/Material.h>
#include <Components/ArrowComponent.h>
#include <Bullet.h>
#include <Kismet/GameplayStatics.h>
#include "CPP_ShootingGameModeBase.h"
#include "PlayerMove.h"


// Sets default values
APlayerCPP::APlayerCPP()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BoxComponent �߰��ϱ�
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	// BoxComponent �� ��Ʈ������Ʈ�� ����
	RootComponent = boxComp;

	// StaticMeshComponent �߰��ϱ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	// ��Ʈ�� �ڽ����� �������
	meshComp->SetupAttachment(boxComp);
	// �浹 ������ ����
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Arrowcomponent �߰�
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	firePosition->SetupAttachment(boxComp);
	firePosition->SetRelativeLocation(FVector(0, 0, 10));

	// StaticMesh ������ �������� �ε��ؼ� �Ҵ��ϱ�
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	// �ּ��� ���������� �ε� �ߴٸ� true �� ����
	if (TempMesh.Succeeded())
	{
		// �о���� �����͸� �Ҵ�
		meshComp->SetStaticMesh(TempMesh.Object);
	}
	// ���� �ε��ϱ�
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	// �ּ��� ���������� �ε� �ߴٸ� true �� ����
	if (TempMat.Succeeded())
	{
		// �о���� �����͸� �Ҵ�
		meshComp->SetMaterial(0, TempMat.Object);
	}

	// PlayerMove ������Ʈ �߰��ϱ�
	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));
}

// Called when the game starts or when spawned
void APlayerCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
// ����ڰ� �����س��� �Է� ���� ó���� �Լ��� �����ִ� ����
void APlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	playerMove->SetupPlayerInputComponent(PlayerInputComponent);

	// Fire ��ư �Է� ���ε�ó��
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerCPP::YogaFire);
}

// �Ѿ˹߻� ó��
void APlayerCPP::YogaFire()
{
	// �Ѿ��� �Ѿ� ���忡�� ������.
	// ���鶧 �� �ڸ��� �ٸ� �༮�� �ִ��� ����� ������ ����
	/*FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ABullet>(bulletFactory,
		firePosition->GetComponentLocation(),
		firePosition->GetComponentRotation(), Param);*/

	// GameMode Ŭ������ GetBullet �� �̿��Ͽ� �Ѿ� ��������
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());

	// gamemode �� ���°� playing �� �ƴ϶�� �Ʒ� �ڵ�� ������� �ʵ��� �ϰ� �ʹ�.
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	// ���� ���ӿ��尡 �ִٸ�
	if (gameMode)
	{
		auto bullet = gameMode->GetBullet();
		if (bullet == nullptr)
		{
			PRINTLOG(TEXT("Error, Empty Bullet Object Pool!!!"));
			return;
		}
		// �ι�° �Ѿ� ���� �ö� źâ�� �Ѿ��� ���̻� ���ٸ�
		// �߻� �� �� ���� ������ ù��° ������ �Ѿ��� �ٽ� źâ�� �ݳ��Ѵ�.
		auto bullet2 = gameMode->GetBullet();
		if (bullet2 == nullptr)
		{
			gameMode->AddBullet(bullet);
			PRINTLOG(TEXT("Error, Empty Bullet Object Pool!!!"));
			return;
		}

		// �ѹ� �߻��Ѵ�.
		gameMode->SetBulletActive(bullet, true);
		// ��ġ��Ų��.
		bullet->SetActorLocation(firePosition->GetComponentLocation() + FVector(0, 25, 0));
		bullet->SetActorRotation(firePosition->GetComponentRotation());
		
		// �ѹ� �߻��Ѵ�.
		gameMode->SetBulletActive(bullet2, true);
		// ��ġ��Ų��.
		bullet2->SetActorLocation(firePosition->GetComponentLocation() + FVector(0, -25, 0));
		bullet2->SetActorRotation(firePosition->GetComponentRotation());
	}
	// �Ѿ� �߻� ���� ���
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);
}