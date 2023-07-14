// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/Stage_Player.h"


// Sets default values
AStage_Player::AStage_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}

// Called when the game starts or when spawned
void AStage_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStage_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStage_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		// ������ ������ ����?
		// DefaultPawn_MoveForward �߰��Ǵ°� ��
		// ����θ� �ϰ� �ֽ��ϴ�.
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::S, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::D, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerTurn", EKeys::MouseX, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

	

		
	}

	// Ű�� �Լ��� �����մϴ�.
	// �� Ű�� ������ �� �Լ��� ����������ε�.
	// ���϶��� �ϴ� ��� ���������.
	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &AStage_Player::MoveForward);
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &AStage_Player::MoveRight);
	PlayerInputComponent->BindAxis("PlayerTurn", this, &AStage_Player::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &AStage_Player::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &AStage_Player::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("PlayerLookUpRate", this, &AStage_Player::LookUpAtRate);

	
}


void AStage_Player::MoveRight(float Val)
{
	
	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);

			
			
			return;
		}
	}
	
	
}

void AStage_Player::MoveForward(float Val)
{
	

	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
		
			return;
		}
	}
	

}


void AStage_Player::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void AStage_Player::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}