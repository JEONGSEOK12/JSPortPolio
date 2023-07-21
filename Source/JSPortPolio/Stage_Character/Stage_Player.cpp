// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/Stage_Player.h"
#include "Components/CapsuleComponent.h"
#include "Stage_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"


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
	Gravity.Set(0, 0, -1000);
	GroundPoint.Set(0, 0, 300);

	TArray<UActorComponent*> Findid = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Player_Collision"));
	UCapsuleComponent* FindScene = Cast<UCapsuleComponent>(Findid[0]);
	

	FindScene->OnComponentHit.AddDynamic(this, &AStage_Player::HitGround);
}

// Called every frame
void AStage_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	//GetMovementComponent()->Velocity += Gravity * DeltaTime;
	TestVec = GetMovementComponent()->Velocity;
	if (bJumpPressed)
	{
		fJumpTime += DeltaTime;
	}
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

		
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJump"), EKeys::SpaceBar));

		
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
	
	PlayerInputComponent->BindAction("PlayerJump" , IE_Pressed , this, &AStage_Player::PlayerJumpStart);
	PlayerInputComponent->BindAction("PlayerJump", IE_Released, this, &AStage_Player::PlayerJumpEnd);

	
}


void AStage_Player::HitGround(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("Terrain")))
	{
		FVector ZeroVec;
		ZeroVec.Set(0, 0, 0);
		GetMovementComponent()->Velocity = ZeroVec;
		bisGround = true;
	}
}


void AStage_Player::MoveRight(float Val)
{

	if (Val != 0.f)
	{
		if (Controller)
		{



			//TArray<UActorComponent*> Findid = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("Player_Collision"));
			//TArray<UActorComponent*> Findid2 = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("Ground_X"));
			//
			//if (bisGround)
			if (Val > 0.f)
			{
				FVector NewLocation = GroundPoint;

				// declare size of radius to move around
				FVector Radius = FVector(0, 100, 0);

				Mydeg += 3;

				FVector RotateValue = Radius.RotateAngleAxis(Mydeg, FVector(-1, 0, 0));

				NewLocation.X += RotateValue.X;
				NewLocation.Y += RotateValue.Y;
				NewLocation.Z += RotateValue.Z;

				SetActorLocation(NewLocation);

				FVector Dir = GroundPoint - GetActorLocation();
				FRotator Rot = Dir.Rotation();
				SetActorRotation(Rot);
			}
			//else
			//{
			//	USceneComponent* FindScene = Cast<USceneComponent>(Findid[0]);
			//
			//	FRotator RotateRight;
			//	if (Val < 0)
			//	{
			//		RotateRight.Add(0, 0, -6);
			//	}
			//
			//	if (Val > 0)
			//	{
			//		RotateRight.Add(0, 0, 6);
			//	}
			//	FindScene->AddLocalRotation(RotateRight);
			//}
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
			

			TArray<UActorComponent*> Findid = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("Player_Collision"));
			TArray<UActorComponent*> Findid2 = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("Ground_X"));

			if (bisGround)
			{
				USceneComponent* FindScene2 = Cast<USceneComponent>(Findid2[0]);

				FRotator RotateForward;
				if (Val < 0)
				{
					RotateForward.Add(3, 0, 0);
				}

				if (Val > 0)
				{
					RotateForward.Add(-3, 0, 0);
				}
				FindScene2->AddLocalRotation(RotateForward);

			}
			else
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

void AStage_Player::PlayerJumpStart()
{
	bJumpPressed = true;
	
	
	//AddMovementInput()
	
}


void AStage_Player::PlayerJumpEnd()
{

	//TArray<UActorComponent*> Findid = GetComponentsByTag(UCharacterMovementComponent::StaticClass(), TEXT("Player_MoveCom"));
	//UCharacterMovementComponent* FindScene = Cast<UCharacterMovementComponent>(Findid[0]);
	

	TArray<UActorComponent*> Findid2 = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("UpBody"));
	USceneComponent* FindScene2 = Cast<USceneComponent>(Findid2[0]);


	FVector JumpVec;

	JumpVec = FindScene2->GetUpVector() * fJumpTime * 1000.0f;

	GetMovementComponent()->Velocity = JumpVec;
	bJumpPressed = false;

	bisGround = false;
	fJumpTime = 0.f;
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

