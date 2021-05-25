// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPP_Shooting.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

// 타겟을 따라서 이동하고 싶다.
// 필요속성 : 타겟
UCLASS()
class CPP_SHOOTING_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;

	// 이동속도
	UPROPERTY(EditAnywhere, Category = "Stat")
	float speed = 500;

	// 필요속성 : 타겟
	UPROPERTY(VisibleAnywhere, Category="Target")
	class AActor* target;

	UPROPERTY()
	FVector dir = FVector(0, 0, 0);
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 충돌 이벤트 처리 함수
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
