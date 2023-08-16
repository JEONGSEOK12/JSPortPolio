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



}

// Called to bind functionality to input
void ATest_Head::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}



void ATest_Head::BodyHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	

	if (OtherActor->ActorHasTag(TEXT("Terrain")))
	{
		BodyBounce(Hit);

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
	GetMovementComponent()->Velocity = PlayerPtr->TestVec1 * 1000.0f + GetMovementComponent()->Velocity * 0.5f;

	PlayerPtr->bisSpined = false;
	PlayerPtr->RotVFX->SetVisibility(false);
	PlayerPtr->RotCheckX = 0.f;
	PlayerPtr->RotCheckY = 0.f;


}
