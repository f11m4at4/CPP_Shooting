// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCPP.generated.h"

// BoxCollider 컴포넌트를 추가하고 싶다.
UCLASS()
class CPP_SHOOTING_API APlayerCPP : public APawn
{
	GENERATED_BODY()

public:
	// 접근권한
	//UPROPERTY(EditAnywhere, EditDefaultsOnly, EditInstanceOnly, VisibleAnywhere, VisibleDefaultsOnly, VisibleInstanceOnly)
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadWrite)

	UPROPERTY(VisibleAnywhere, Category="Component")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;

public:
	// Sets default values for this pawn's properties
	APlayerCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
