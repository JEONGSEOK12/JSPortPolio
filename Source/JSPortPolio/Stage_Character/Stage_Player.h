// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	void JumpAction(float Rate);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};