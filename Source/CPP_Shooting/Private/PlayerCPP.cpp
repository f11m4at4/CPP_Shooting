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

	// PlayerMove 컴포넌트 추가하기
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
// 사용자가 정의해놓은 입력 값과 처리할 함수를 묶어주는 역할
void APlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	playerMove->SetupPlayerInputComponent(PlayerInputComponent);

	// Fire 버튼 입력 바인딩처리
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerCPP::YogaFire);
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

	// gamemode 의 상태가 playing 이 아니라면 아래 코드는 실행되지 않도록 하고 싶다.
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	// 만약 게임오드가 있다면
	if (gameMode)
	{
		auto bullet = gameMode->GetBullet();
		if (bullet == nullptr)
		{
			PRINTLOG(TEXT("Error, Empty Bullet Object Pool!!!"));
			return;
		}
		// 두번째 총알 가져 올때 탄창에 총알이 더이상 없다면
		// 발사 할 수 없기 때문에 첫번째 가져온 총알은 다시 탄창에 반납한다.
		auto bullet2 = gameMode->GetBullet();
		if (bullet2 == nullptr)
		{
			gameMode->AddBullet(bullet);
			PRINTLOG(TEXT("Error, Empty Bullet Object Pool!!!"));
			return;
		}

		// 한발 발사한다.
		gameMode->SetBulletActive(bullet, true);
		// 배치시킨다.
		bullet->SetActorLocation(firePosition->GetComponentLocation() + FVector(0, 25, 0));
		bullet->SetActorRotation(firePosition->GetComponentRotation());
		
		// 한발 발사한다.
		gameMode->SetBulletActive(bullet2, true);
		// 배치시킨다.
		bullet2->SetActorLocation(firePosition->GetComponentLocation() + FVector(0, -25, 0));
		bullet2->SetActorRotation(firePosition->GetComponentRotation());
	}
	// 총알 발사 사운드 재생
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);
}