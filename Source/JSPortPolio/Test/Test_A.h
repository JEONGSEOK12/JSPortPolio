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


	FVector BeginLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Head");
	TSubclassOf<ACharacter> MyHead;



	class ATest_B* Head;

};
