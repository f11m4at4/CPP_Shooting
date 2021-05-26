// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Materials/Material.h>
#include <Components/ArrowComponent.h>
#include <Bullet.h>
#include <Kismet/GameplayStatics.h>



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
}

// Called when the game starts or when spawned
void APlayerCPP::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
}

// Called every frame
void APlayerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���������� �̵����Ѻ���
	// P = P0 + vt
	// RightVector -> (x, y, z) (0, 1, 0)
	//FVector v(0, 1, 0);
	//FVector v = FVector(0, 1, 1);
	// 1. ������ �ʿ��ϴ�.
	FVector vel = FVector(0, h, v);
	vel.Normalize();
	//v = v * 500;
	vel *= speed;

	FVector P0 = GetActorLocation();
	FVector P = P0 + vel * DeltaTime;
	// 2. ��ġ�� �����ϰ� �ʹ�. -> �̵��ϰ�ʹ�.
	SetActorLocation(P, true);

	// Yaw ������ ȸ���ϰ� �ʹ�.
	// R = R0 + rt
	/*FRotator R0 = GetActorRotation();
	FRotator r = FRotator(0, 1, 0) * 100;
	FRotator R = R0 + r * DeltaTime;
	SetActorRotation(R);*/
}

// Called to bind functionality to input
// ����ڰ� �����س��� �Է� ���� ó���� �Լ��� �����ִ� ����
void APlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerCPP::InputHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerCPP::InputVertical);

	// Fire ��ư �Է� ���ε�ó��
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerCPP::YogaFire);
}

// ������� Horizontal �Է� ó���� �Լ�
void APlayerCPP::InputHorizontal(float value)
{
	h = value;
}

void APlayerCPP::InputVertical(float value)
{
	v = value;
}

// �Ѿ˹߻� ó��
void APlayerCPP::YogaFire()
{
	// �Ѿ��� �Ѿ� ���忡�� ������.
	// ���鶧 �� �ڸ��� �ٸ� �༮�� �ִ��� ����� ������ ����
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ABullet>(bulletFactory,
		firePosition->GetComponentLocation(),
		firePosition->GetComponentRotation(), Param);

	// �Ѿ� �߻� ���� ���
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);
}