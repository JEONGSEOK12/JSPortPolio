// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/Stage_Player.h"
#include "Components/CapsuleComponent.h"
#include "Stage_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>


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
	GroundPoint.Set(0,0,300);
	RadiusX = FVector(0, 0, 100);
	RadiusY = FVector(100, 0, 0);
	RotSpeed = 4;


	TArray<UActorComponent*> Findid1 = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Player_Collision"));
	UCapsuleComponent* FindScene1 = Cast<UCapsuleComponent>(Findid1[0]);
	FindScene1->OnComponentHit.AddDynamic(this, &AStage_Player::LandGround);


	TArray<UActorComponent*> Findid2 = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Player_Body"));
	UCapsuleComponent* FindScene2 = Cast<UCapsuleComponent>(Findid2[0]);
	FindScene2->OnComponentBeginOverlap.AddDynamic(this, &AStage_Player::OverlapGround);


	//UPrimitiveComponent, OnComponentHit, UPrimitiveComponent*, HitComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, FVector, NormalImpulse, const FHitResult&, Hit);


}

// Called every frame
void AStage_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(bisGround)
	{
	
	}
	else
	{
		GetMovementComponent()->Velocity += Gravity * DeltaTime;
	}

	


	
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
	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &AStage_Player::MoveForward);
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &AStage_Player::MoveRight);
	PlayerInputComponent->BindAxis("PlayerTurn", this, &AStage_Player::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &AStage_Player::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &AStage_Player::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("PlayerLookUpRate", this, &AStage_Player::LookUpAtRate);
	
	PlayerInputComponent->BindAction("PlayerJump" , IE_Pressed , this, &AStage_Player::PlayerJumpStart);
	PlayerInputComponent->BindAction("PlayerJump", IE_Released, this, &AStage_Player::PlayerJumpEnd);

	
}


void AStage_Player::LandGround(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("Terrain")))
	{
		FVector ZeroVec;
		ZeroVec.Set(0, 0, 0);
		GetMovementComponent()->Velocity = ZeroVec;
		bisGround = true;
		GroundPoint = Hit.Location - (87 * GetActorUpVector());
		bUseControllerRotationYaw = true;
	}
}

void AStage_Player::OverlapGround(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("Terrain")))
	{
	TestVec1 = SweepResult.ImpactPoint;
	TestVec2 = GetActorLocation();
	TestVec3 = TestVec2 - TestVec1;
	GetMovementComponent()->Velocity = TestVec3;

	int a = 0;

	}
}


void AStage_Player::MoveRight(float Val)
{
	FVector ForVec;
	ForVec.Set(1, 0, 0);

	if (bisGround)
	{
		if (Val != 0.f)
		{
			if (Controller)
			{
				GroundRotation(ForVec, -RotSpeed * Val);
			}
		}
	}
	else
	{
		BodyRotation(ForVec, -RotSpeed * 2 * Val);
	}
}

void AStage_Player::MoveForward(float Val)
{
	FVector RitVec;
	RitVec.Set(0, 1, 0);

	if(bisGround)
	{
		if (Val != 0.f)
		{
			if (Controller)
			{
				GroundRotation(RitVec, RotSpeed * Val);
			}
		}
	}
	else
	{
		BodyRotation(RitVec, RotSpeed * 2 * Val);
	}

}

void AStage_Player::BodyRotation(FVector Dir, double Speed)
{
	Dir.Normalize();
	FQuat AddQuat = FQuat(Dir, Speed * 0.01f);
	MyCurQuat = GetActorQuat();
	MyCurQuat = MyCurQuat * AddQuat;
	SetActorRotation(MyCurQuat);
}

void AStage_Player::GroundRotation(FVector Dir,double Speed)
{	
	BodyRotation(Dir, Speed);

	FVector UpVec = MyCurQuat.GetUpVector();
	UpVec.Normalize();
	UpVec = UpVec * 87;
	FVector CurLocation = GroundPoint + UpVec;
	SetActorLocation(CurLocation);
}

void AStage_Player::PlayerJumpStart()
{
	bJumpPressed = true;
}


void AStage_Player::PlayerJumpEnd()
{	
	TArray<UActorComponent*> Findid2 = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("UpBody"));
	USceneComponent* FindScene2 = Cast<USceneComponent>(Findid2[0]);

	FVector JumpVec;
	JumpVec = FindScene2->GetUpVector() * fJumpTime * 1000.0f;

	GetMovementComponent()->Velocity = JumpVec;
	bJumpPressed = false;
	bUseControllerRotationYaw = false;
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

