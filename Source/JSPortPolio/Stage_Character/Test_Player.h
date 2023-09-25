// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputDatas");
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputDatas");
	class UInputDataAsset* InputDatas;


	class UNiagaraComponent* Niagara;

	class USpringArmComponent* MySpringArm;

	UFUNCTION()
	void LandGround(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);



	ACharacter* Spawned_Head;

	class ATest_Head* HeadPtr;

	float fFowardAccel;

	float fFowardSpeed;

	float fRightAccel;

	float fRightSpeed;

	float fTurnAccel;

	float fTurnSpeed;

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

	

	float RotCheckX;
	float RotCheckY;
	float RotCheckZ;

	FVector LandVec;

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

	void PlayerSimpleMove(FVector Dir, const float Val);
	void PlayerMove(FVector Dir, float OwnParameter);


	void GroundRotation(FVector Dir, const  float Speed);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	
	

	void MoveForward(const struct FInputActionValue& Val);
	void MoveForwardEnd();
	void MoveRight(const struct FInputActionValue& Val);
	void MoveRightEnd();
	void MoveTurn(const struct FInputActionValue& Val);
	void MoveTurnEnd();

	void PlayerJumpStart();
	void PlayerJumpOngoing();
	void PlayerJumpTriggered();
	void PlayerJumpCanceled();
	void PlayerJumpEnd();
	
	
	void HeadRotation(FVector Dir, const float Speed);
	void CameraReset();

	void MoveMouse(const struct FInputActionValue& Val);


};
