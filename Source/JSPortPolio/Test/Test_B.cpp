// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/Test_B.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
ATest_B::ATest_B()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATest_B::BeginPlay()
{
	Super::BeginPlay();

	

}

// Called every frame
void ATest_B::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector UpVec;
	UpVec.Set(0, 0, 100);

	GetMovementComponent()->Velocity = UpVec;




}

// Called to bind functionality to input
void ATest_B::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

