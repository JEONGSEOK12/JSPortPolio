// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/Stage_Player.h"
#include "Components/CapsuleComponent.h"
#include "Stage_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "Particles/ParticleSystemComponent.h"
#include "Stage_Character/Stage_Player_Head.h"
#include "Kismet/GameplayStatics.h"



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
	RotSpeed = 2;
	



	TArray<UActorComponent*> Findid1 = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Player_Collision"));
	UCapsuleComponent* FindScene1 = Cast<UCapsuleComponent>(Findid1[0]);
	FindScene1->OnComponentHit.AddDynamic(this, &AStage_Player::LandGround);


	AHead = GetWorld()->SpawnActor<ACharacter>(Head);
	AHead->SetActorLocation(GetActorLocation());

	Headptr = Cast<AStage_Player_Head>(AHead);

	Headptr->XRotTime = 0;
	Headptr->YRotTime = 0;
	Headptr->bisGround = false;
	Headptr->PlayerPtr = this;

	GetWorld()->GetFirstPlayerController()->Possess(AHead);


}

// Called every frame
void AStage_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetMovementComponent()->Velocity += Gravity * DeltaTime;

	if (Headptr->XRotTime > 60 || Headptr->YRotTime > 60)
	{
		Headptr->bRotated = true;
	}

	if (Headptr->bRotated == true)
	{
		//begin effect
	}
	else
	{
		//end effect
	}

	

	if (Headptr->bisGround)
	{
		FVector SetVector = GetActorUpVector();
		SetVector.Normalize();
		AHead->SetActorLocation(GetActorLocation() + SetVector * 100);
		FQuat SetQuat = GetActorQuat();
		AHead->SetActorRotation(SetQuat);
	}
	else
	{
	
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
	
	PlayerInputComponent->BindAction("PlayerJump", IE_Pressed, this, &AStage_Player::PlayerJumpStart);

	
}


void AStage_Player::LandGround(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("Terrain")))
	{
		FVector ZeroVec;
		ZeroVec.Set(0, 0, 0);
		GetMovementComponent()->Velocity = ZeroVec;
		Headptr->bisGround = true;
		bUseControllerRotationYaw = true;
		Headptr->XRotTime = 0;
		Headptr->YRotTime = 0;
		Headptr->bRotated = false;
		GetWorld()->GetFirstPlayerController()->Possess(this);

	}
}


void AStage_Player::MoveRight(float Val)
{
	FVector ForVec;
	ForVec.Set(1, 0, 0);

	if (Headptr->bisGround)
	{
		if (Val != 0.f)
		{
			if (Controller)
			{
				GroundRotation(ForVec, -RotSpeed * 1* Val);
			}
		}
	}
	else
	{
		return;
	}
}

void AStage_Player::MoveForward(float Val)
{
	FVector RitVec;
	RitVec.Set(0, 1, 0);

	if(Headptr->bisGround)
	{
		if (Val != 0.f)
		{
			if (Controller)
			{
				GroundRotation(RitVec, RotSpeed * 1 * Val);
			}
		}
	}
	else
	{
		return;
	}

}


void AStage_Player::GroundRotation(FVector Dir,double Speed)
{	
	Dir.Normalize();
	FQuat AddQuat = FQuat(Dir, Speed * 0.01f);
	MyCurQuat = GetActorQuat();
	MyCurQuat = MyCurQuat * AddQuat;
	SetActorRotation(MyCurQuat);
}




void AStage_Player::PlayerJumpStart()
{
	Headptr->bJumpPressed = true;

	GetWorld()->GetFirstPlayerController()->Possess(AHead);

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

