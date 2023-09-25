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
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include <Datas/InputDataAsset.h>



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

	


}

// Called every frame
void ATest_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	fDeltaSec = DeltaTime;


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

	APlayerController* PlayerCon = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* System = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerCon->GetLocalPlayer());

	System->ClearAllMappings();
	System->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* PIE = Cast< UEnhancedInputComponent>(PlayerInputComponent);

	PIE->BindAction(InputDatas->MoveForward, ETriggerEvent::Triggered, this, &ATest_Player::MoveForward);
	PIE->BindAction(InputDatas->MoveForward, ETriggerEvent::Completed, this, &ATest_Player::MoveForwardEnd);

	PIE->BindAction(InputDatas->MoveRight, ETriggerEvent::Triggered, this, &ATest_Player::MoveRight);
	PIE->BindAction(InputDatas->MoveRight, ETriggerEvent::Completed, this, &ATest_Player::MoveRightEnd);

	PIE->BindAction(InputDatas->MoveTurn, ETriggerEvent::Triggered, this, &ATest_Player::MoveTurn);
	PIE->BindAction(InputDatas->MoveTurn, ETriggerEvent::Completed, this, &ATest_Player::MoveTurnEnd);

	PIE->BindAction(InputDatas->MoveMouse, ETriggerEvent::Triggered, this, &ATest_Player::MoveMouse);

	PIE->BindAction(InputDatas->Jump, ETriggerEvent::Started, this, &ATest_Player::PlayerJumpStart);
	PIE->BindAction(InputDatas->Jump, ETriggerEvent::Triggered, this, &ATest_Player::PlayerJumpTriggered);
	PIE->BindAction(InputDatas->Jump, ETriggerEvent::Completed, this, &ATest_Player::PlayerJumpEnd);

	PIE->BindAction(InputDatas->CameraReset, ETriggerEvent::Started, this, &ATest_Player::CameraReset);

}


void ATest_Player::GroundRotation(FVector Dir, float Speed)
{
	Dir.Normalize();

	FQuat AddQuat = FQuat(Dir, Speed);
	MyCurQuat = GetActorQuat();
	MyCurQuat = MyCurQuat * AddQuat;
	SetActorRotation(MyCurQuat);
}

void ATest_Player::HeadRotation(FVector Dir, float Speed)
{
	Dir.Normalize();
	FQuat AddQuat = FQuat(Dir, Speed);
	MyHeadCurQuat = HeadPtr->GetActorQuat();
	MyHeadCurQuat = MyHeadCurQuat * AddQuat;
	HeadPtr->SetActorRotation(MyHeadCurQuat);
}

void ATest_Player::PlayerSimpleMove(FVector Dir, float Val)
{
	if (bisGround)
	{
		if (Val != 0.f)
		{
			GroundRotation(Dir, Val);
		}
	}
	else
	{
		if (Val != 0.f)
		{
			HeadRotation(Dir, Val);
		}
	}
}

void ATest_Player::PlayerMove(FVector Dir, float Val)
{
	if (RotMaxSpeed >= abs(Val))
	{
		PlayerSimpleMove(Dir, Val);
		RotCheckX += Val;

	}
	else
	{
		if (Val >= 0)
		{
			Val = RotMaxSpeed;
		}
		else
		{
			Val = -RotMaxSpeed;
		}
		PlayerSimpleMove(Dir, Val);

		RotCheckX += RotMaxSpeed;
	}

}

void ATest_Player::MoveForward(const FInputActionValue& Val)
{
	FVector ForVec;
	ForVec.Set(0, 1, 0);

	fFowardAccel += fDeltaSec * 0.1f * Val.Get<float>();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Jump Triggered %f"), fFowardAccel));

	PlayerMove(ForVec, fFowardAccel);

}

void ATest_Player::MoveForwardEnd()
{
	fFowardAccel = 0;
}

void ATest_Player::MoveRight(const FInputActionValue& Val)
{
	FVector RitVec;
	RitVec.Set(-1, 0, 0);

	fRightAccel += fDeltaSec * 0.1f * Val.Get<float>();

	PlayerMove(RitVec, fRightAccel);
}

void ATest_Player::MoveRightEnd()
{
	fRightAccel = 0;
}

void ATest_Player::MoveTurn(const FInputActionValue& Val)
{
	FVector TurnVec;
	TurnVec.Set(0, 0, 1);

	fTurnAccel += fDeltaSec * 0.1f * Val.Get<float>();

	PlayerMove(TurnVec, fTurnAccel);
}

void ATest_Player::MoveTurnEnd()
{
	fTurnAccel = 0;
}

void ATest_Player::MoveMouse(const FInputActionValue& Val)
{
	FVector2D Mouse = Val.Get<FVector2D>();

	if (Mouse.X != 0.f && Mouse.Y != 0.f)
	{
		FRotator ArmRot = MySpringArm->GetRelativeRotation();

		ArmRot = ArmRot + FRotator(Mouse.Y, Mouse.X, 0);

		MySpringArm->SetRelativeRotation(ArmRot);

	}

}

void ATest_Player::CameraReset()
{
	FRotator ResetRot = MySpringArm->GetRelativeRotation();
	ResetRot.Yaw = GetActorRotation().Yaw;
	ResetRot.Roll = 0;
	MySpringArm->SetRelativeRotation(ResetRot);
}


void ATest_Player::PlayerJumpStart()
{
	bJumpPressed = true;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Jump started")));
}

void ATest_Player::PlayerJumpTriggered()
{
	if (fJumpTime <= fMaxJumpTime)
	{
		fJumpTime += fDeltaSec;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Jump Triggered")));

}


void ATest_Player::PlayerJumpEnd()
{
	if (bisGround)
	{
		FVector JumpVec;
		JumpVec = HeadPtr->GetActorUpVector() * fJumpTime * fJumpPower;

		if (bisSpined)
		{
			HeadPtr->GetMovementComponent()->Velocity = HeadPtr->GetActorUpVector() * LandVec.Size();

			FVector TTT = HeadPtr->GetMovementComponent()->Velocity;
			double Tes = TTT.Size();

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Spined %f"), Tes));
		}
		else
		{
			HeadPtr->GetMovementComponent()->Velocity = JumpVec + HeadPtr->GetActorUpVector() * fBasicJumpPoawer;

			FVector TTT = HeadPtr->GetMovementComponent()->Velocity;
			double Tes = TTT.Size();

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("JumpEnded %f"), Tes));
		}

		bisSpined = false;
		//RotVFX->SetVisibility(false);
		fJumpTime = 0.f;
		bJumpPressed = false;
		bisGround = false;
	}

}


void ATest_Player::LandGround(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("Terrain")) && DebugTime > 0.1f)
	{


		if (!bJumpPressed)
		{
			bisGround = true;

			HeadPtr->GetMovementComponent()->Velocity.Set(0, 0, 0);
			GetMovementComponent()->Velocity.Set(0, 0, 0);

			PlayerJumpEnd();
			return;
		}

		LandVec = HeadPtr->GetMovementComponent()->Velocity;

		HeadPtr->GetMovementComponent()->Velocity.Set(0, 0, 0);
		GetMovementComponent()->Velocity.Set(0, 0, 0);

		HeadPtr->HitPower = 0.f;
		RotCheckX = 0.f;
		RotCheckY = 0.f;
		bisGround = true;
		DebugTime = 0.f;


	}

	if (OtherActor->ActorHasTag(TEXT("Monster")) && DebugTime > 0.1f)
	{

		HeadPtr->GetMovementComponent()->Velocity.Set(0, 0, 0);

		HeadPtr->GetMovementComponent()->Velocity = HeadPtr->GetActorUpVector() * fBasicJumpPoawer * 1.5f;

		ACharacter_Base* Monster = Cast<ACharacter_Base>(OtherActor);
		
		// 나중에 바꿀것
		Monster->HP -= 100;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("MonsterHit")));

		RotCheckX = 0.f;
		RotCheckY = 0.f;
		DebugTime = 0.f;


	}

}



