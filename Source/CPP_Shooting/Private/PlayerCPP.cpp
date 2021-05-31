// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Materials/Material.h>
#include <Components/ArrowComponent.h>
#include <Bullet.h>
#include <Kismet/GameplayStatics.h>
#include "CPP_ShootingGameModeBase.h"


// Sets default values
APlayerCPP::APlayerCPP()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BoxComponent 추가하기
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	// BoxComponent 를 루트컴포넌트로 설정
	RootComponent = boxComp;

	// StaticMeshComponent 추가하기
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	// 루트의 자식으로 등록하자
	meshComp->SetupAttachment(boxComp);
	// 충돌 없도록 설정
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Arrowcomponent 추가
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	firePosition->SetupAttachment(boxComp);
	firePosition->SetRelativeLocation(FVector(0, 0, 10));

	// StaticMesh 데이터 동적으로 로드해서 할당하기
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	// 애셋을 성공적으로 로드 했다면 true 를 리턴
	if (TempMesh.Succeeded())
	{
		// 읽어들인 데이터를 할당
		meshComp->SetStaticMesh(TempMesh.Object);
	}
	// 재질 로드하기
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	// 애셋을 성공적으로 로드 했다면 true 를 리턴
	if (TempMat.Succeeded())
	{
		// 읽어들인 데이터를 할당
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

	// 오른쪽으로 이동시켜보자
	// P = P0 + vt
	// RightVector -> (x, y, z) (0, 1, 0)
	//FVector v(0, 1, 0);
	//FVector v = FVector(0, 1, 1);
	// 1. 방향이 필요하다.
	FVector vel = FVector(0, h, v);
	vel.Normalize();
	//v = v * 500;
	vel *= speed;

	FVector P0 = GetActorLocation();
	FVector P = P0 + vel * DeltaTime;
	// 2. 위치를 지정하고 싶다. -> 이동하고싶다.
	SetActorLocation(P, true);

	// Yaw 축으로 회전하고 싶다.
	// R = R0 + rt
	/*FRotator R0 = GetActorRotation();
	FRotator r = FRotator(0, 1, 0) * 100;
	FRotator R = R0 + r * DeltaTime;
	SetActorRotation(R);*/
}

// Called to bind functionality to input
// 사용자가 정의해놓은 입력 값과 처리할 함수를 묶어주는 역할
void APlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerCPP::InputHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerCPP::InputVertical);

	// Fire 버튼 입력 바인딩처리
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerCPP::YogaFire);
}

// 사용자의 Horizontal 입력 처리할 함수
void APlayerCPP::InputHorizontal(float value)
{
	h = value;
}

void APlayerCPP::InputVertical(float value)
{
	v = value;
}

// 총알발사 처리
void APlayerCPP::YogaFire()
{
	// 총알을 총알 공장에서 만들자.
	// 만들때 그 자리에 다른 녀석이 있더라도 만들어 지도록 설정
	/*FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ABullet>(bulletFactory,
		firePosition->GetComponentLocation(),
		firePosition->GetComponentRotation(), Param);*/

	// GameMode 클래스의 GetBullet 을 이용하여 총알 가져오기
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	// 만약 게임오드가 있다면
	if (gameMode)
	{
		auto bullet = gameMode->GetBullet();
		if (bullet == nullptr)
		{
			PRINTLOG(TEXT("Error, Empty Bullet Object Pool!!!"));
			return;
		}
		// 활성화 시켜준다.
		gameMode->SetBulletActive(bullet, true);
		// 배치시킨다.
		bullet->SetActorLocation(firePosition->GetComponentLocation());
		bullet->SetActorRotation(firePosition->GetComponentRotation());
	}
	// 총알 발사 사운드 재생
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);
}