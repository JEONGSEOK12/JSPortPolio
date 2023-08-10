// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/Test_Player.h"
#include "Stage_Character/Test_Head.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	fJumpPower = 500.0f;
	fMaxJumpTime = 2.0f;


	RotSpeed = 4;

	Gravity.Set(0, 0, -500);


	TArray<UActorComponent*> Findid1 = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Leg"));
	UCapsuleComponent* FindScene1 = Cast<UCapsuleComponent>(Findid1[0]);
	FindScene1->OnComponentHit.AddDynamic(this, &ATest_Player::LandGround);


	TArray<UActorComponent*> Findid2 = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Body"));
	UCapsuleComponent* FindScene2 = Cast<UCapsuleComponent>(Findid2[0]);
	FindScene2->OnComponentBeginOverlap.AddDynamic(this, &ATest_Player::Bodyoverlap);



}

// Called every frame
void ATest_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GetMovementComponent()->Velocity += Gravity * DeltaTime;
	//HeadPtr->GetMovementComponent()->Velocity += Gravity * DeltaTime;
	
	if (bJumpPressed)
	{
		if(fJumpTime<= fMaxJumpTime)
		{
			fJumpTime += DeltaTime;
		}
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
			SetActorLocation(GetActorLocation());
			GetMovementComponent()->Velocity.Set(0, 0, 0);
			
			bisGround = true;
			DebugTime = 0.f;
		}
		

	}
}

void ATest_Player::Bodyoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag(TEXT("Terrain")))
	{



		//if (bisGround)
		{
	

			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; // 히트 가능한 오브젝트 유형들.
			TEnumAsByte<EObjectTypeQuery> Terrain = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic); //히트 필터
			ObjectTypes.Add(Terrain);
			FHitResult HitResult;
			TArray<AActor*> IgnoreActors;


			//TestVec = SweepResult.ImpactPoint;
			bool isHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), HeadPtr->GetActorLocation(), HeadPtr->GetActorLocation(), 100.0f, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, true);


			if (isHit)
			{
				bisGround = false;

				TestVec = HitResult.Normal;
				TestVec.Normalize();


				HeadPtr->GetMovementComponent()->Velocity = TestVec * 1000.0f;
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Checked!"));
			}

		}



	}

}


void ATest_Player::GroundRotation(FVector Dir, double Speed)
{
	Dir.Normalize();
	FQuat AddQuat = FQuat(Dir, Speed * 0.01f);
	MyCurQuat = GetActorQuat();
	MyCurQuat = MyCurQuat * AddQuat;
	SetActorRotation(MyCurQuat);
}

void ATest_Player::HeadRotation(FVector Dir, double Speed)
{
	Dir.Normalize();
	FQuat AddQuat = FQuat(Dir, Speed * 0.01f);
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
		GroundRotation(ForVec, -RotSpeed * 1 * Val);
		}
	}
	else
	{
		if (Val != 0.f)
		{
		HeadRotation(ForVec, -RotSpeed * 1 * Val);
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
		HeadRotation(RitVec, RotSpeed * 1 * Val);
		}
	}

}




void ATest_Player::PlayerJumpStart()
{
	bJumpPressed = true;
	//GetWorld()->GetFirstPlayerController()->Possess(HeadPtr);
}

void ATest_Player::PlayerJumpEnd()
{
	if(bisGround)
	{
		FVector JumpVec;
		JumpVec = HeadPtr->GetActorUpVector() * fJumpTime * fJumpPower;
		HeadPtr->GetMovementComponent()->Velocity = JumpVec;
		fJumpTime = 0;
		bJumpPressed = false;

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
