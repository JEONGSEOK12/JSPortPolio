// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/Test_A.h"
#include "Test/Test_B.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ATest_A::ATest_A()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATest_A::BeginPlay()
{
	Super::BeginPlay();

	Head = GetWorld()->SpawnActor<ATest_B>(MyHead);
	
	BeginLoc.Set(0, 0, 300);
	Head->SetActorLocation(BeginLoc);

	//FVector UpVec;
	//UpVec.Set(0, 0, 100);
	//
	//GetCharacterMovement()->Velocity = UpVec;

}

// Called every frame
void ATest_A::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//Head->GetCharacterMovement()->Velocity = UpVec;
	//GetCharacterMovement()->Velocity = UpVec;
	//Head->AddActorLocalOffset(UpVec);
}

// Called to bind functionality to input
void ATest_A::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

