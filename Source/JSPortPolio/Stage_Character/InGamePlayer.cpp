// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/InGamePlayer.h"

// Sets default values
AInGamePlayer::AInGamePlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

	RootComponent = Scene;
	
	m_mcomp = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("CharacterMovementComponent"));
	if (m_mcomp)
	{
		m_mcomp->UpdatedComponent = Scene;
	}
	m_mcomp->UpdatedComponent = RootComponent;
	

}

// Called when the game starts or when spawned
void AInGamePlayer::BeginPlay()
{
	Super::BeginPlay();
	
	Gravity.Set(0, 0, -100);


}

// Called every frame
void AInGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_mcomp->Velocity = Gravity;

	//AddMovementInput(Gravity, 100);
}

// Called to bind functionality to input
void AInGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

