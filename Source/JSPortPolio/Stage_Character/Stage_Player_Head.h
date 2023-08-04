// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Stage_Player_Head.generated.h"

UCLASS()
class JSPORTPOLIO_API AStage_Player_Head : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStage_Player_Head();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	FVector Gravity;
	bool bJumpPressed;
	float fJumpTime;

	float RotSpeed;
	FQuat MyCurQuat;
	bool bisGround;
	bool bRotated;


	class AStage_Player* PlayerPtr;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn");
	float XRotTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn");
	float YRotTime;


	void HeadRotation(FVector Dir, double Speed);
	
	void PlayerJumpEnd();


	void MoveRight(float Val);
	void MoveForward(float Val);





};
