// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/Stage_Player_Head.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Stage_Character/Stage_Player.h"







// Sets default values
AStage_Player_Head::AStage_Player_Head()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStage_Player_Head::BeginPlay()
{
	Super::BeginPlay();
	
	Gravity.Set(0, 0, -1000);


	

}

// Called every frame
void AStage_Player_Head::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetMovementComponent()->Velocity += Gravity * DeltaTime;
	
	if (bJumpPressed)
	{
		fJumpTime += DeltaTime;
	}


	if (bisGround)
	{

		FVector DownVector = -GetActorUpVector();
		DownVector.Normalize();
		//SetActorLocation(AHead->GetActorLocation() + DownVector * 100);
		FQuat SetQuat = GetActorQuat();
		//SetActorRotation(SetQuat);

		//SetActorLocation(AHead->GetActorLocation() + DownVector * 100);
	}
	else
	{
		FVector SetVector = GetActorUpVector();
		SetVector.Normalize();
		PlayerPtr->SetActorLocation(GetActorLocation() + -SetVector * 100,true);
		FQuat SetQuat = GetActorQuat();
		PlayerPtr->SetActorRotation(SetQuat);
	}

	


}

// Called to bind functionality to input
void AStage_Player_Head::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJump"), EKeys::SpaceBar));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::S, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::D, 1.f));



	}

	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &AStage_Player_Head::MoveForward);
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &AStage_Player_Head::MoveRight);

	PlayerInputComponent->BindAction("PlayerJump", IE_Pressed, this, &AStage_Player_Head::PlayerJumpStart);
	PlayerInputComponent->BindAction("PlayerJump", IE_Released, this, &AStage_Player_Head::PlayerJumpEnd);

}

void AStage_Player_Head::HeadRotation(FVector Dir, double Speed)
{
	Dir.Normalize();
	FQuat AddQuat = FQuat(Dir, Speed * 0.01f);
	MyCurQuat = GetActorQuat();
	MyCurQuat = MyCurQuat * AddQuat;
	SetActorRotation(MyCurQuat);
}

void AStage_Player_Head::MoveRight(float Val)
{
	FVector ForVec;
	ForVec.Set(1, 0, 0);

	if (bisGround)
	{
		return;
	}
	else
	{
		if (Val != 0.f)
		{
			HeadRotation(ForVec, -RotSpeed * 2 * Val);
			YRotTime += Val;
		}
	}
}

void AStage_Player_Head::MoveForward(float Val)
{
	FVector RitVec;
	RitVec.Set(0, 1, 0);

	if (bisGround)
	{
		return;
	}
	else
	{

		if (Val != 0.f)
		{
			HeadRotation(RitVec, RotSpeed * 2 * Val);
			XRotTime += Val;
		}
	}

}


void AStage_Player_Head::PlayerJumpStart()
{
	bJumpPressed = true;
}


void AStage_Player_Head::PlayerJumpEnd()
{

	FVector JumpVec;
	JumpVec = GetActorUpVector() * fJumpTime * -1000.0f;

	if (bRotated == true)
	{
		//spawn effect
	}

	GetMovementComponent()->Velocity = JumpVec;
	bJumpPressed = false;
	bUseControllerRotationYaw = false;
	bisGround = false;
	fJumpTime = 0.f;
}