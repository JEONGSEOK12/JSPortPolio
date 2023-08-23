// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Test_Head.generated.h"

UCLASS()
class JSPORTPOLIO_API ATest_Head : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATest_Head();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void BodyHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void BodyBounce(const FHitResult& Hit);
	
	void Rotation(FVector Dir, double Speed);

	class ATest_Player* PlayerPtr;

	FVector RotVec;

	FQuat MyCurQuat;

	double HitPower;


};
