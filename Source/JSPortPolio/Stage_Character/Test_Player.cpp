// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/Test_Player.h"
#include "Stage_Character/Test_Head.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
ATest_Player::ATest_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATest_Player::BeginPlay()
{
	Super::BeginPlay();
	FVector SetLoc;
	SetLoc.Set(0, 0, 200);
	Spawned_Head = GetWorld()->SpawnActor<ACharacter>(Test_Head);
	Spawned_Head->SetActorLocation(SetLoc);
	HeadPtr = Cast<ATest_Head>(Spawned_Head);
	HeadPtr->PlayerPtr = this;

	RotSpeed = 2;

	Gravity.Set(0, 0, -1000);

}

// Called every frame
void ATest_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetMovementComponent()->Velocity += Gravity * DeltaTime;

	if (bisGround)
	{	
		FVector HeadLoc;
		HeadLoc = GetActorLocation() + GetActorUpVector() * 100.0f;
		
		HeadPtr->SetActorLocation(HeadLoc);
	}
	else
	{
		FVector PlayerLoc;
		PlayerLoc = HeadPtr->GetActorLocation() + HeadPtr->GetActorUpVector() * -100.0f;

		SetActorLocation(PlayerLoc);
	}


}

// Called to bind functionality to input
void ATest_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::S, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::D, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerTurn", EKeys::MouseX, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJump"), EKeys::SpaceBar));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJump"), EKeys::SpaceBar));
	}


	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &ATest_Player::MoveForward);
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &ATest_Player::MoveRight);
	PlayerInputComponent->BindAxis("PlayerTurn", this, &ATest_Player::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &ATest_Player::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &ATest_Player::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("PlayerLookUpRate", this, &ATest_Player::LookUpAtRate);

	PlayerInputComponent->BindAction("PlayerJump", IE_Pressed, this, &ATest_Player::PlayerJumpStart);

	PlayerInputComponent->BindAction("PlayerJump", IE_Released, this, &ATest_Player::PlayerJumpEnd);
}

void ATest_Player::GroundRotation(FVector Dir, double Speed)
{
	Dir.Normalize();
	FQuat AddQuat = FQuat(Dir, Speed * 0.01f);
	MyCurQuat = GetActorQuat();
	MyCurQuat = MyCurQuat * AddQuat;
	SetActorRotation(MyCurQuat);
}

void ATest_Player::MoveRight(float Val)
{
	FVector ForVec;
	ForVec.Set(1, 0, 0);

	if (bisGround)
	{
		if (Val != 0.f)
		{	
		GroundRotation(ForVec, -RotSpeed * 1 * Val);
		}
	}
	else
	{
		if (Val != 0.f)
		{
		HeadPtr->HeadRotation(ForVec, -RotSpeed * 1 * Val);
		}
	}
}

void ATest_Player::MoveForward(float Val)
{
	FVector RitVec;
	RitVec.Set(0, 1, 0);

	if (bisGround)
	{
		if (Val != 0.f)
		{
		GroundRotation(RitVec, RotSpeed * 1 * Val);
		}
	}
	else
	{
		if (Val != 0.f)
		{
		HeadPtr->HeadRotation(RitVec, -RotSpeed * 1 * Val);
		}
	}

}




void ATest_Player::PlayerJumpStart()
{
	HeadPtr->bJumpPressed = true;
	//GetWorld()->GetFirstPlayerController()->Possess(HeadPtr);
}

void ATest_Player::PlayerJumpEnd()
{
	FVector JumpVec;
	JumpVec = HeadPtr->GetActorUpVector() * HeadPtr->fJumpTime * 100.0f;
	HeadPtr->GetMovementComponent()->Velocity = JumpVec;
	HeadPtr->fJumpTime = 0;

	


}



void ATest_Player::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void ATest_Player::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}
