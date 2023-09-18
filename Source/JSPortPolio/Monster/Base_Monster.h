// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Datas/CharacterDatas.h>
#include "Character_Base.h"

#include "Base_Monster.generated.h"

UCLASS()
class JSPORTPOLIO_API ABase_Monster : public ACharacter_Base
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABase_Monster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters");
	float WalkSpeed;

	class USkeletalMeshComponent* MeshComponent;

	class USplineComponent* SplineComponent;


};
