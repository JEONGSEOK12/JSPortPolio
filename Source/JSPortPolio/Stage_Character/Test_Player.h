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

	ACharacter* Spawned_Head;

	class ATest_Head* HeadPtr;

	FQuat MyCurQuat;

	bool bisGround = false;

	float RotSpeed;

	FVector Gravity;

	

	void GroundRotation(FVector Dir, double Speed);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void MoveRight(float Val);
	void MoveForward(float Val);
	void PlayerJumpStart();
	void PlayerJumpEnd();



};