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

	if (bJumpPressed)
	{
		fJumpTime += DeltaTime;
	}

}

// Called to bind functionality to input
void ATest_Head::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJump"), EKeys::SpaceBar));
	}
	PlayerInputComponent->BindAction("PlayerJump", IE_Released, this, &ATest_Head::PlayerJumpEnd);
}

void ATest_Head::HeadRotation(FVector Dir, double Speed)
{
	Dir.Normalize();
	FQuat AddQuat = FQuat(Dir, Speed * 0.01f);
	MyCurQuat = GetActorQuat();
	MyCurQuat = MyCurQuat * AddQuat;
	SetActorRotation(MyCurQuat);
}

void ATest_Head::PlayerJumpEnd()
{
	FVector JumpVec;
	JumpVec = GetActorUpVector() * fJumpTime * -1000.0f;
	GetMovementComponent()->Velocity = JumpVec;
	fJumpTime = 0;

	GetWorld()->GetFirstPlayerController()->Possess(PlayerPtr);


}








