// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPP_Shooting.h"
#include "GameFramework/Pawn.h"
#include "PlayerCPP.generated.h"

// BoxCollider ������Ʈ�� �߰��ϰ� �ʹ�.
//����ڰ� �߻� ��ư�� ������ �Ѿ��� �߻��ϰ� �ʹ�.
// �ʿ�Ӽ� : �ѱ���ġ, ����
//1. ����ڰ� �߻� ��ư�� �������ϱ�
//2. �Ѿ��� ������ �Ѵ�.
//3. �Ѿ��� ��ġ��Ų��.
UCLASS()
class CPP_SHOOTING_API APlayerCPP : public APawn
{
	GENERATED_BODY()

public:
	// ���ٱ���
	//UPROPERTY(EditAnywhere, EditDefaultsOnly, EditInstanceOnly, VisibleAnywhere, VisibleDefaultsOnly, VisibleInstanceOnly)
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadWrite)

	UPROPERTY(VisibleAnywhere, Category="Component")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;

	// �ʿ�Ӽ� : �ѱ���ġ, ����
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UArrowComponent* firePosition;
	//// ����
	//UPROPERTY(EditDefaultsOnly, Category = "BulletClass")
	//TSubclassOf<class ABullet> bulletFactory;

	// �Ѿ� �߻� ����
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* bulletSound;

	// �Ѿ� �߻� ó���� �Լ�
	void YogaFire();

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


public:
	// �¿� �Է°� ó�� �Լ� ����
	// Axis �Է��� ó���� �Լ��� ���� void �Լ��̸�(float);
	void InputHorizontal(float value);
	// ���� �Է°� ó�� �Լ� ����
	void InputVertical(float value);

	// �¿� �Է��� �޾��� �� �ش� �������� �̵��ϰ� �ʹ�.
	UPROPERTY()
	float h = 0;
	UPROPERTY()
	float v = 0;

	UPROPERTY(EditAnywhere, Category="Stat")
	float speed = 500;
};
