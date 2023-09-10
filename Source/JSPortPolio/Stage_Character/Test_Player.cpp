// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/Test_Player.h"
#include "Stage_Character/Test_Head.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PhysicsVolume.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include <Character_Base.h>




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
	Spawned_Head->SetActorLocation(GetActorLocation());
	HeadPtr = Cast<ATest_Head>(Spawned_Head);
	HeadPtr->PlayerPtr = this;
	MySpringArm = Cast<USpringArmComponent>(GetComponentByClass(USpringArmComponent::StaticClass()));

	GetMovementComponent()->GetPhysicsVolume()->FluidFriction = 0;


	TArray<UActorComponent*> Findid1 = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Leg"));
	UCapsuleComponent* FindScene1 = Cast<UCapsuleComponent>(Findid1[0]);
	FindScene1->OnComponentHit.AddDynamic(this, &ATest_Player::LandGround);

	//TArray<UActorComponent*> Findid3 = GetComponentsByTag(UNiagaraComponent::StaticClass(), TEXT("RotVFX"));
	//RotVFX = Cast<UNiagaraComponent>(Findid3[0]);
	//
	//
	//RotVFX->SetVisibility(false);

	//fJumpPower = 600.0f;
	//fMaxJumpTime = 2.0f;
	//RotSpeed = 4.f;
	//SpinCheck = 5.f;
	//fBasicJumpPoawer = 600.f;
	//Gravity.Set(0, 0, -200);



}

// Called every frame
void ATest_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	fDeltaSec = DeltaTime;
	FVector TTT = HeadPtr->GetMovementComponent()->Velocity;
	TestD = TTT.Size();

	Testf += DeltaTime;
	if (Testf >= 0.1f && TestD != 0.f)
	{
		Testf = 0.f;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Vec is %f"), TestD));
	}


	if (bJumpPressed)
	{
		if (fJumpTime <= fMaxJumpTime)
		{
			fJumpTime += DeltaTime;
		}
	}

	if (RotCheckX >= SpinCheck || RotCheckY >= SpinCheck)
	{
		bisSpined = true;
		//RotVFX->SetVisibility(true);
	}



	if (bisGround)
	{

		FVector HeadLoc;
		HeadLoc = GetActorLocation() + GetActorUpVector() * 140.0f;

		HeadPtr->SetActorLocation(HeadLoc, true);
		HeadPtr->SetActorRotation(GetActorQuat());

	}
	else
	{
		GetMovementComponent()->Velocity += Gravity * DeltaTime;
		HeadPtr->GetMovementComponent()->Velocity += Gravity * DeltaTime;


		DebugTime += DeltaTime;

		FVector PlayerLoc;
		PlayerLoc = HeadPtr->GetActorLocation() + HeadPtr->GetActorUpVector() * -140.0f;

		SetActorLocation(PlayerLoc, true);
		SetActorRotation(HeadPtr->GetActorQuat());
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

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerRotate", EKeys::E, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerRotate", EKeys::Q, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerTurnRate", EKeys::MouseX, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, 1.f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerCameraReset"), EKeys::F));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJump"), EKeys::SpaceBar));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJump"), EKeys::SpaceBar));
	}


	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &ATest_Player::MoveForward);
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &ATest_Player::MoveRight);
	PlayerInputComponent->BindAxis("PlayerRotate", this, &ATest_Player::Rotate);

	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &ATest_Player::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &ATest_Player::LookUpAtRate);

	PlayerInputComponent->BindAction("PlayerCameraReset", IE_Pressed, this, &ATest_Player::PlayerCameraResetStart);

	PlayerInputComponent->BindAction("PlayerJump", IE_Pressed, this, &ATest_Player::PlayerJumpStart);

	PlayerInputComponent->BindAction("PlayerJump", IE_Released, this, &ATest_Player::PlayerJumpEnd);

}

void ATest_Player::PlayerCameraResetStart()
{
	FRotator ResetRot = MySpringArm->GetRelativeRotation();
	ResetRot.Yaw = GetActorRotation().Yaw;
	ResetRot.Roll = 0;
	MySpringArm->SetRelativeRotation(ResetRot);
	
}

void ATest_Player::LandGround(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("Terrain")))
	{


		if (DebugTime > 0.1f)
		{

			if (!bJumpPressed)
			{
				bisGround = true;

				HeadPtr->GetMovementComponent()->Velocity.Set(0, 0, 0);
				GetMovementComponent()->Velocity.Set(0, 0, 0);

				PlayerJumpEnd();
				return;
			}


			TestVec1 = HeadPtr->GetMovementComponent()->Velocity;
			double Tes = TestVec1.Size();



			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Terrain Land Power is %f"), Tes));

			CurVec = GetMovementComponent()->Velocity;



			HeadPtr->GetMovementComponent()->Velocity.Set(0, 0, 0);
			GetMovementComponent()->Velocity.Set(0, 0, 0);

			HeadPtr->HitPower = 0.f;
			RotCheckX = 0.f;
			RotCheckY = 0.f;
			bisGround = true;
			DebugTime = 0.f;
		}

	}

	if (OtherActor->ActorHasTag(TEXT("Monster")))
	{

		if (DebugTime > 0.1f)
		{
			CurVec = GetMovementComponent()->Velocity;
			HeadPtr->GetMovementComponent()->Velocity.Set(0, 0, 0);
			//SetActorLocation(GetActorLocation());
			//GetMovementComponent()->Velocity.Set(0, 0, 0);
			//
			//HeadPtr->SetActorLocation(GetActorLocation());
			//HeadPtr->GetMovementComponent()->Velocity.Set(0, 0, 0);

			HeadPtr->GetMovementComponent()->Velocity = HeadPtr->GetActorUpVector() * fBasicJumpPoawer * 1.5f;

			ACharacter_Base* Monster = Cast<ACharacter_Base>(OtherActor);
			Monster->HP -= 100;
			if (Monster->HP <= 0)
			{
				Monster->Destroy();
			}

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("MonsterHit")));

			RotCheckX = 0.f;
			RotCheckY = 0.f;
			DebugTime = 0.f;
		}

	}

}



void ATest_Player::GroundRotation(FVector Dir, double Speed)
{
	Dir.Normalize();
	FQuat AddQuat = FQuat(Dir, Speed * fDeltaSec);
	MyCurQuat = GetActorQuat();
	MyCurQuat = MyCurQuat * AddQuat;
	SetActorRotation(MyCurQuat);
}

void ATest_Player::HeadRotation(FVector Dir, double Speed)
{
	Dir.Normalize();
	FQuat AddQuat = FQuat(Dir, Speed * fDeltaSec);
	MyHeadCurQuat = HeadPtr->GetActorQuat();
	MyHeadCurQuat = MyHeadCurQuat * AddQuat;
	HeadPtr->SetActorRotation(MyHeadCurQuat);
}



void ATest_Player::MoveRight(float Val)
{
	FVector ForVec;
	ForVec.Set(1, 0, 0);

	if (bisGround)
	{
		if (Val != 0.f)
		{
			GroundRotation(ForVec, -RotSpeed * Val);
		}
	}
	else
	{
		if (Val != 0.f)
		{
			HeadRotation(ForVec, -RotSpeed * Val);

			RotCheckX += RotSpeed * fDeltaSec * Val;
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
			GroundRotation(RitVec, RotSpeed * Val);
		}
	}
	else
	{
		if (Val != 0.f)
		{
			HeadRotation(RitVec, RotSpeed * Val);

			RotCheckY += RotSpeed * fDeltaSec * Val;
		}
	}

}

void ATest_Player::Rotate(float Val)
{
	FVector RotVec;
	RotVec.Set(0, 0, 1);

	if (bisGround)
	{
		if (Val != 0.f)
		{
			GroundRotation(RotVec, RotSpeed * Val);
		}
	}
	else
	{
		if (Val != 0.f)
		{
			HeadRotation(RotVec, RotSpeed * Val);

			RotCheckZ += RotSpeed * fDeltaSec * Val;
		}
	}
}




void ATest_Player::PlayerJumpStart()
{
	bJumpPressed = true;

}

void ATest_Player::PlayerJumpEnd()
{
	if (bisGround)
	{
		FVector JumpVec;
		JumpVec = HeadPtr->GetActorUpVector() * fJumpTime * fJumpPower;

		if (bisSpined)
		{
			HeadPtr->GetMovementComponent()->Velocity = HeadPtr->GetActorUpVector() * TestVec1.Size();

			FVector TTT = HeadPtr->GetMovementComponent()->Velocity;
			double Tes = TTT.Size();

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Total Jump Power is %f"), Tes));
		}
		else
		{
			HeadPtr->GetMovementComponent()->Velocity = JumpVec + HeadPtr->GetActorUpVector() * fBasicJumpPoawer;

			FVector TTT = HeadPtr->GetMovementComponent()->Velocity;
			double Tes = TTT.Size();

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Total Jump Power is %f"), Tes));
		}

		bisSpined = false;
		//RotVFX->SetVisibility(false);
		fJumpTime = 0.f;
		bJumpPressed = false;
		bisGround = false;



	}




}



void ATest_Player::TurnAtRate(float Rate)
{

	if (Rate != 0.f)
	{
		FRotator ArmRot = MySpringArm->GetRelativeRotation();
		
		ArmRot = ArmRot + FRotator(0, Rate, 0);
		
		MySpringArm->SetRelativeRotation(ArmRot);

	}

}

void ATest_Player::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (Rate != 0.f)
	{
		FRotator ArmRot = MySpringArm->GetRelativeRotation();

		ArmRot = ArmRot + FRotator(Rate, 0, 0);

		MySpringArm->SetRelativeRotation(ArmRot);

	}
}
