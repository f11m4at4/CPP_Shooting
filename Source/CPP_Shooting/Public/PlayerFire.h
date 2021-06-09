// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerFire.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_SHOOTING_API UPlayerFire : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 사용자 입력처리 담당할 함수 콜백
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	// 총알 발사 처리할 함수
	void YogaFire();
	
public:
	// 총알 발사 사운드
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* bulletSound;

	// 소유하고 있는 Actor 객체
	UPROPERTY()
	class APlayerCPP* me;
};
