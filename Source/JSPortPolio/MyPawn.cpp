// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/KismetMathLibrary.h>


// Sets default values
AMyPawn::AMyPawn()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	Gravity.Set(0, 0, -1000);
	GroundPoint.Set(0, 0, 300);
	RadiusX = FVector(0, 0, 100);
	RadiusY = FVector(100, 0, 0);

	TArray<UActorComponent*> Findid = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Player_Collision"));
	UCapsuleComponent* FindScene = Cast<UCapsuleComponent>(Findid[0]);


	FindScene->OnComponentHit.AddDynamic(this, &AMyPawn::HitGround);
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//GetMovementComponent()->Velocity += Gravity * DeltaTime;

	if (bJumpPressed)
	{
		fJumpTime += DeltaTime;
	}
}



// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &AMyPawn::MoveRight);
	PlayerInputComponent->BindAxis("PlayerTurn", this, &AMyPawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &AMyPawn::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &AMyPawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("PlayerLookUpRate", this, &AMyPawn::LookUpAtRate);

	PlayerInputComponent->BindAction("PlayerJump", IE_Pressed, this, &AMyPawn::PlayerJumpStart);
	PlayerInputComponent->BindAction("PlayerJump", IE_Released, this, &AMyPawn::PlayerJumpEnd);


}


void AMyPawn::HitGround(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("Terrain")))
	{
		FVector ZeroVec;
		ZeroVec.Set(0, 0, 0);
		bisGround = true;

		//FComponentHitSignature safd;

	}
}


void AMyPawn::MoveRight(float Val)
{

	if (Val != 0.f)
	{
		if (Controller)
		{

			if (Val > 0.f)
			{

				FVector ForVec = GetActorForwardVector();
				TestVec1 = GetActorForwardVector();

				FQuat AddQuat = FQuat(ForVec, 0.01);
				MyCurQuat = GetActorQuat();
				MyCurQuat = MyCurQuat * AddQuat;

				SetActorRotation(MyCurQuat);
			}
			if (Val < 0.f)
			{

				FVector ForVec = GetActorForwardVector();
				TestVec1 = GetActorForwardVector();

				FQuat AddQuat = FQuat(ForVec, -0.01);
				MyCurQuat = GetActorQuat();
				MyCurQuat = MyCurQuat * AddQuat;

				SetActorRotation(MyCurQuat);

			}

			return;


		}
	}



}

void AMyPawn::MoveForward(float Val)
{

	if (Val != 0.f)
	{
		if (Controller)
		{

			if (Val > 0.f)
			{
				FVector ForVec = GetActorRightVector();
				ForVec.Normalize();
				TestVec1 = GetActorForwardVector();

				FQuat AddQuat = FQuat(ForVec, 0.01);
				MyCurQuat = GetActorQuat();
				MyCurQuat = MyCurQuat * AddQuat;

				SetActorRotation(MyCurQuat);
			}
			if (Val < 0.f)
			{
				FVector ForVec = GetActorRightVector();
				ForVec.Normalize();
				TestVec1 = GetActorForwardVector();

				FQuat AddQuat = FQuat(ForVec, 0.01);
				MyCurQuat = GetActorQuat();
				MyCurQuat = MyCurQuat * AddQuat;

				SetActorRotation(MyCurQuat);
			}
			return;

		}
	}



}


void AMyPawn::PlayerJumpStart()
{
	bJumpPressed = true;


	//AddMovementInput()

}


void AMyPawn::PlayerJumpEnd()
{

	//TArray<UActorComponent*> Findid = GetComponentsByTag(UCharacterMovementComponent::StaticClass(), TEXT("Player_MoveCom"));
	//UCharacterMovementComponent* FindScene = Cast<UCharacterMovementComponent>(Findid[0]);


	TArray<UActorComponent*> Findid2 = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("UpBody"));
	USceneComponent* FindScene2 = Cast<USceneComponent>(Findid2[0]);


	FVector JumpVec;

	JumpVec = FindScene2->GetUpVector() * fJumpTime * 1000.0f;

	bJumpPressed = false;

	bisGround = false;
	fJumpTime = 0.f;
}





void AMyPawn::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void AMyPawn::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

