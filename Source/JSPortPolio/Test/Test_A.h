// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Test_A.generated.h"

UCLASS()
class JSPORTPOLIO_API ATest_A : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATest_A();

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


	FQuat MyCurQuat;
	FQuat MyBodyQuat;
	UCapsuleComponent* MyBody;
	AActor* Casted_Body;
	float RotSpeed;
	bool bisGround;
	FVector Gravity;
	bool bJumpPressed;
	float fJumpTime;
	float JumpPower;






	void MoveRight(float Val);
	void MoveForward(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	UFUNCTION()
		void LandGround(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void PlayerJumpStart();

	void PlayerJumpEnd();

	void GroundRotation(FVector Dir, double Speed);

	void BodyRotation(FVector Dir, double Speed);
	
};
