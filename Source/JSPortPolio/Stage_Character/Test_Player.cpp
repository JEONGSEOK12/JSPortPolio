// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/Test_Player.h"
#include "Stage_Character/Test_Head.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"



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

	TArray<UActorComponent*> Findid1 = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Leg"));
	UCapsuleComponent* FindScene1 = Cast<UCapsuleComponent>(Findid1[0]);
	FindScene1->OnComponentHit.AddDynamic(this, &ATest_Player::LandGround);

	TArray<UActorComponent*> Findid2 = GetComponentsByTag(USphereComponent::StaticClass(), TEXT("Measure"));
	USphereComponent* FindScene2 = Cast<USphereComponent>(Findid2[0]);
	FindScene2->OnComponentBeginOverlap.AddDynamic(this, &ATest_Player::Measure);


	TArray<UActorComponent*> Findid3 = GetComponentsByTag(UNiagaraComponent::StaticClass(), TEXT("RotVFX"));
	RotVFX = Cast<UNiagaraComponent>(Findid3[0]);
	

	RotVFX->SetVisibility(false);

	fMeasured = 0.f;
	bMeasure = false;
	fJumpPower = 600.0f;
	fMaxJumpTime = 2.0f;
	RotCheckX = 0.f;
	RotCheckY = 0.f;
	RotSpeed = 4.f;
	SpinCheck = 5.f;
	fBasicJumpPoawer = 600.f;


	Gravity.Set(0, 0, -1200);
	


}

// Called every frame
void ATest_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	fDeltaSec = DeltaTime;


	if (bJumpPressed)
	{
		if(fJumpTime<= fMaxJumpTime)
		{
			fJumpTime += DeltaTime;
		}
	}

	if (RotCheckX >= SpinCheck || RotCheckY >= SpinCheck)
	{
		bisSpined = true;
		RotVFX->SetVisibility(true);
	}
	
	if (bMeasure)
	{
		fMeasured += DeltaTime;
	}

	if (bisGround)
	{	

		FVector HeadLoc;
		HeadLoc = GetActorLocation() + GetActorUpVector() * 140.0f;

		HeadPtr->SetActorLocation(HeadLoc);
		HeadPtr->SetActorRotation(GetActorQuat());

	}
	else
	{
		GetMovementComponent()->Velocity += Gravity * DeltaTime;
		HeadPtr->GetMovementComponent()->Velocity += Gravity * DeltaTime;


		DebugTime += DeltaTime;

		FVector PlayerLoc;
		PlayerLoc = HeadPtr->GetActorLocation() + HeadPtr->GetActorUpVector() * -140.0f;

		SetActorLocation(PlayerLoc);
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

void ATest_Player::LandGround(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("Terrain")))
	{

		


		if(DebugTime>0.5f)
		{
			TestVec1 = GetMovementComponent()->Velocity;

			SetActorLocation(GetActorLocation());
			GetMovementComponent()->Velocity.Set(0, 0, 0);

			
			
			RotCheckX = 0.f;
			RotCheckY = 0.f;
			bisGround = true;
			DebugTime = 0.f;
		}
		

	}
}


void ATest_Player::Measure(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{

	FVector Test123 = GetActorLocation();


	if (OtherActor->ActorHasTag(TEXT("Terrain")))
	{
		bMeasure = true;

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




void ATest_Player::PlayerJumpStart()
{
	bJumpPressed = true;

}

void ATest_Player::PlayerJumpEnd()
{
	if(bisGround)
	{
		FVector JumpVec;
		JumpVec = HeadPtr->GetActorUpVector() * fJumpTime * fJumpPower;

		if(bisSpined)
		{
			HeadPtr->GetMovementComponent()->Velocity = HeadPtr->GetActorUpVector() * TestVec1.Size() + HeadPtr->GetActorUpVector() * 200;
		}
		else
		{
			HeadPtr->GetMovementComponent()->Velocity = JumpVec + HeadPtr->GetActorUpVector() * fBasicJumpPoawer;
		}


		fMeasured = 0.f;
		fJumpTime = 0.f;
		bJumpPressed = false;
		bMeasure = false;
		bisGround = false;
	}


	

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
