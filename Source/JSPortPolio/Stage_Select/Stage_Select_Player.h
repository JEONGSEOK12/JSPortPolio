// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Stage_Select_Player.generated.h"

UCLASS()
class JSPORTPOLIO_API AStage_Select_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStage_Select_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void JumpAction();
	void JumpAxis(float Rate);

	void MoveRight(float Val);
	void MoveForward(float Val);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseLookUpRate;

	bool AxisJump = false;

};