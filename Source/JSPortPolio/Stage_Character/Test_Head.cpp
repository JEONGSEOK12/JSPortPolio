// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/Test_Head.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Stage_Character/Test_Player.h"




// Sets default values
ATest_Head::ATest_Head()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATest_Head::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATest_Head::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

// Called to bind functionality to input
void ATest_Head::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}









