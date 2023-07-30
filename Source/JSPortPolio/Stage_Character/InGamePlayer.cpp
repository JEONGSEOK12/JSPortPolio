// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/InGamePlayer.h"

// Sets default values
AInGamePlayer::AInGamePlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AInGamePlayer::BeginPlay()
{
	Super::BeginPlay();
	
	TestPoint.Set(0, 0, 300);
	TestPoint.Normalize();
	Timespent = 0;


}

// Called every frame
void AInGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AddMovementInput(Gravity, 100);

	Timespent += DeltaTime;

	FVector LookVec = TestPoint - GetActorLocation();
	LookVec.Normalize();
	LookVec.Set(1, 1, 0);

	FQuat MyQa = FQuat(LookVec, Timespent * PI / 4.f);
	SetActorRotation(MyQa);


}

// Called to bind functionality to input
void AInGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

