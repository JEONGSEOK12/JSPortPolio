// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/Test_Head.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Stage_Character/Test_Player.h"




// Sets default values
ATest_Head::ATest_Head()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATest_Head::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UActorComponent*> Findid1 = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Body"));
	UCapsuleComponent* FindScene1 = Cast<UCapsuleComponent>(Findid1[0]);
	FindScene1->OnComponentHit.AddDynamic(this, &ATest_Head::BodyHit);



}

// Called every frame
void ATest_Head::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HitPower >= 1.0f)
	{
		Rotation(RotVec, HitPower/100 * DeltaTime );
		HitPower -= HitPower * DeltaTime + 100.f * DeltaTime;


	}

}

// Called to bind functionality to input
void ATest_Head::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}


void ATest_Head::Rotation(FVector Dir, double Speed)
{
	Dir.Normalize();
	FQuat AddQuat = FQuat(Dir, Speed);	
	MyCurQuat = GetActorQuat();
	MyCurQuat = MyCurQuat * AddQuat;
	SetActorRotation(MyCurQuat);
}



void ATest_Head::BodyHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	

	if (OtherActor->ActorHasTag(TEXT("Terrain")))
	{

		HitPower = PlayerPtr->TestD;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("HeadHit Power is %f"), HitPower));


		BodyBounce(Hit);


		FVector ImpactVec = Hit.ImpactPoint - GetActorLocation();
		FVector CurVec = GetMovementComponent()->Velocity;
		CurVec.Normalize();
		RotVec = FVector::CrossProduct(ImpactVec,CurVec);
		
		

	}

	if (OtherActor->ActorHasTag(TEXT("Monster")))
	{
		BodyBounce(Hit);



	}


}


void ATest_Head::BodyBounce(const FHitResult& Hit)
{



	PlayerPtr->bisGround = false;
	PlayerPtr->TestVec1 = Hit.ImpactNormal;

	FVector Vec = GetMovementComponent()->Velocity;

	GetMovementComponent()->Velocity.Set(0, 0, 0);

	GetMovementComponent()->Velocity = PlayerPtr->TestVec1 * 1000.0f + Vec * 0.5f;

	PlayerPtr->bisSpined = false;
	//PlayerPtr->RotVFX->SetVisibility(false);
	PlayerPtr->RotCheckX = 0.f;
	PlayerPtr->RotCheckY = 0.f;


}
