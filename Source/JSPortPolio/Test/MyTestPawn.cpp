// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/MyTestPawn.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyTestPawn::AMyTestPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChracterMoveCom = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("PawnMovementComponent"));
	ChracterMoveCom->UpdatedComponent = RootComponent;

}

// Called when the game starts or when spawned
void AMyTestPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyTestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

