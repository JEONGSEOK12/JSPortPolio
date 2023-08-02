// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Stage_PlayerController.h"
#include "Stage_Player.generated.h"

UCLASS()
class JSPORTPOLIO_API AStage_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStage_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
		float BaseTurnRate = 45.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
		float BaseLookUpRate = 45.0f;

	void MoveRight(float Val);
	void MoveForward(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void PlayerJumpStart();
	void PlayerJumpEnd();

	UFUNCTION()
	void LandGround(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	

	void GroundRotation(FVector Dir,double Speed);
	void BodyRotation(FVector Dir, double Speed);



	bool bisGround;


	FVector Gravity;
	bool bJumpPressed;
	bool bRotated;
	FQuat MyCurQuat;
	float RotSpeed;
	float fJumpTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn");
	float XRotTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn");
	float YRotTime;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn");
	FVector TestVec1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn");
	FVector TestVec2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn");
	FVector TestVec3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn");
	FQuat TestQuat2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn");
	TSubclassOf<AActor> Head;
	
	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
