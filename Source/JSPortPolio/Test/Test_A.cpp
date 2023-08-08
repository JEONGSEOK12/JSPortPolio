// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/Test_A.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ATest_A::ATest_A()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATest_A::BeginPlay()
{
	Super::BeginPlay();
	RotSpeed = 2;

	TArray<UActorComponent*> FindArr = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Body"));
	MyBody = Cast<UCapsuleComponent>(FindArr[0]);
	Casted_Body = Cast<AActor>(MyBody);

	JumpPower = 1000.0f;

	bisGround = true;
	
	Gravity.Set(0, 0, -10);

	TArray<UActorComponent*> Findid1 = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Leg"));
	UCapsuleComponent* FindScene1 = Cast<UCapsuleComponent>(Findid1[0]);
	FindScene1->OnComponentHit.AddDynamic(this, &ATest_A::LandGround);

	TArray<UActorComponent*> Findid2 = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("Leg"));
	Check_Scene = Cast<USceneComponent>(Findid2[0]);
	
	

}

// Called every frame
void ATest_A::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetMovementComponent()->Velocity += Gravity + DeltaTime;

	if (bJumpPressed)
	{
		fJumpTime += DeltaTime;
	}
	
}

// Called to bind functionality to input
void ATest_A::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		// 여기의 내용은 뭐냐?
		// DefaultPawn_MoveForward 추가되는것 뿐
		// 축매핑만 하고 있스니다.
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::S, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::D, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerTurn", EKeys::MouseX, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJump"), EKeys::SpaceBar));


	}

	// 키와 함수를 연결합니다.
	// 이 키가 눌리면 이 함수를 실행시켜줘인데.
	// 축일때는 일단 계속 실행시켜줘.
	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &ATest_A::MoveForward);
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &ATest_A::MoveRight);
	PlayerInputComponent->BindAxis("PlayerTurn", this, &ATest_A::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &ATest_A::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &ATest_A::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("PlayerLookUpRate", this, &ATest_A::LookUpAtRate);

	PlayerInputComponent->BindAction("PlayerJump", IE_Pressed, this, &ATest_A::PlayerJumpStart);
	PlayerInputComponent->BindAction("PlayerJump", IE_Released, this, &ATest_A::PlayerJumpEnd);

}





void ATest_A::LandGround(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("Terrain")))
	{

		FVector Distance = Check_Scene->GetComponentLocation() - GetActorLocation();
		
		if (Distance.Size()>=1.0f)
		{
			FVector CheckVec;
			CheckVec = Check_Scene->GetComponentLocation();
			FQuat BodyQuat;
			BodyQuat = MyBody->GetComponentQuat();
			SetActorLocation(CheckVec);
			SetActorRotation(BodyQuat);
			return;
		}

		FVector ZeroVec;
		ZeroVec.Set(0, 0, 0);
		GetMovementComponent()->Velocity = ZeroVec;

		bisGround = true;
	}

}

void ATest_A::PlayerJumpStart()
{
	bJumpPressed = true;
}

void ATest_A::PlayerJumpEnd()
{



	FVector JumpVec = MyBody->GetUpVector() * fJumpTime * JumpPower;
	GetMovementComponent()->Velocity = JumpVec;

	fJumpTime = 0.0f;
	bJumpPressed = false;


	bisGround = false;
}

void ATest_A::GroundRotation(FVector Dir, double Speed)
{
	Dir.Normalize();
	FQuat AddQuat = FQuat(Dir, Speed * 0.01f);
	MyCurQuat = GetActorQuat();
	MyCurQuat = MyCurQuat * AddQuat;
	SetActorRotation(MyCurQuat);

}

void ATest_A::BodyRotation(FVector Dir, double Speed)
{
	Dir.Normalize();
	FQuat AddQuat = FQuat(Dir, Speed * 0.01f);
	
	
	MyBodyQuat = MyBody->GetComponentQuat();
	MyBodyQuat = MyBodyQuat * AddQuat;
	MyBody->SetWorldRotation(MyBodyQuat);

	
}

void ATest_A::MoveRight(float Val)
{
	FVector ForVec;
	ForVec.Set(1, 0, 0);

	
	if (Val != 0.f)
	{
		if (bisGround)
		{
			GroundRotation(ForVec, RotSpeed * 1 * Val);
		}
		else
		{
			BodyRotation(ForVec, RotSpeed * 1 * Val);
		}

	}

}

void ATest_A::MoveForward(float Val)
{
	FVector RitVec;
	RitVec.Set(0, 1, 0);

	
	
	if (Val != 0.f)
	{
			if (bisGround)
			{
				GroundRotation(RitVec, RotSpeed * 1 * Val);
			}
			else
			{
				BodyRotation(RitVec, -RotSpeed * 1 * Val);
			}


	}

}

void ATest_A::TurnAtRate(float Rate)
{

}

void ATest_A::LookUpAtRate(float Rate)
{

}






