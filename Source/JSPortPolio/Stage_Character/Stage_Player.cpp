// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/Stage_Player.h"
#include "Components/CapsuleComponent.h"


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
	Gravity.Set(0, 0, -1);
	AddMovementInput(Gravity, 1000);

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

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerJump", EKeys::SpaceBar, 1.f));
		//UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJump"), EKeys::SpaceBar));

		
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
	PlayerInputComponent->BindAxis("PlayerJump", this, &AStage_Player::PlayerJump);
	//PlayerInputComponent->BindAction("PlayerJump" , IE_Pressed , this, &AStage_Player::PlayerJump) // �Լ��� �ν��Ͻ��� ���ٴ°� ������?
	
}


void AStage_Player::MoveRight(float Val)
{
	
	if (Val != 0.f)
	{
		if (Controller)
		{



			TArray<UActorComponent*> Findid = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("BODY_X"));
		
						
			if (0 != Findid.Num())
			{
				USceneComponent* FindScene = Cast<USceneComponent>(Findid[0]);

				FRotator RotateRight;
				if (Val < 0)
				{
					RotateRight.Add(0, 0, -6);
				}

				if (Val > 0)
				{
					RotateRight.Add(0, 0, 6);
				}
				FindScene->AddLocalRotation(RotateRight);
			}
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
			

			TArray<UActorComponent*> Findid = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("BODY_X"));


			if (0 != Findid.Num())
			{
				USceneComponent* FindScene = Cast<USceneComponent>(Findid[0]);

				FRotator RotateFoward;
				if (Val < 0)
				{
					RotateFoward.Add(6, 0, 0);
				}

				if (Val > 0)
				{
					RotateFoward.Add(-6, 0, 0);
				}
				FindScene->AddLocalRotation(RotateFoward);
			}
			return;
		}
	}
	

}

void AStage_Player::PlayerJump(float Val)
{
	if (Val != 0.f)
	{
		Jump();
		TArray<UActorComponent*> Findid = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("UpBody"));
		USceneComponent* FindScene = Cast<USceneComponent>(Findid[0]);

		AddMovementInput(-FindScene->GetUpVector(),100000);
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