// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NiagaraComponent.h"
#include "Test_Player.generated.h"

UCLASS()
class JSPORTPOLIO_API ATest_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATest_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
		float BaseTurnRate = 45.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
		float BaseLookUpRate = 45.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Head");
	TSubclassOf<ACharacter> Test_Head;

	class USpringArmComponent* MySpringArm;

	UFUNCTION()
	void LandGround(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);



	ACharacter* Spawned_Head;

	class ATest_Head* HeadPtr;


	float fDeltaSec;

	FQuat MyCurQuat;

	FQuat MyHeadCurQuat;

	bool bJumpPressed;

	float fJumpTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters");
	float fBasicJumpPoawer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters");
	float fMaxJumpTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters");
	float fJumpPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters");
	float RotIniSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters");
	float RotMaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters");
	float RotAccel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters");
	FVector Gravity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters");
	float SpinCheck;

	bool bisGround = false;

	bool bisSpined;

	UNiagaraComponent* RotVFX;

	float RotCheckX;
	float RotCheckY;
	float RotCheckZ;

	FVector CurVec;

	float DebugTime;

	double TestD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn");
	FVector TestVec1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn");
	FVector TestVec2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn");
	FVector TestVec3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn");
	AActor* TestAc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn");
	float Testf;


	void GroundRotation(FVector Dir, double Speed);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void MoveRight(float Val);
	void MoveForward(float Val);
	void Rotate(float Val);
	void PlayerJumpStart();
	void PlayerJumpEnd();
	void HeadRotation(FVector Dir, double Speed);
	void PlayerCameraResetStart();

};
