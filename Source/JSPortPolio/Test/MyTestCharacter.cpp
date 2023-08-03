// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/MyTestCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyTestCharacter::AMyTestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyTestCharacter::BeginPlay()
{
	Super::BeginPlay();
	AHead = GetWorld()->SpawnActor<ACharacter>(Head);
	FVector BeginVec;
	BeginVec.Set(100, 0, 200);
	AHead->SetActorLocation(BeginVec);
}

// Called every frame
void AMyTestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MoveVec;
	MoveVec.Set(0, 0, 10);
	AHead->GetMovementComponent()->Velocity += MoveVec * DeltaTime;
	//AHead->AddActorWorldOffset(MoveVec * DeltaTime);

}

// Called to bind functionality to input
void AMyTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

