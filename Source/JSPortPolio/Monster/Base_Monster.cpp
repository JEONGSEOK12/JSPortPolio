// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Base_Monster.h"
#include <Datas/CharacterDatas.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SplineComponent.h"


// Sets default values
ABase_Monster::ABase_Monster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABase_Monster::BeginPlay()
{
	Super::BeginPlay();


	SplineComponent = Cast<USplineComponent>(GetComponentByClass(USplineComponent::StaticClass()));

	MeshComponent = Cast<UMeshComponent>(GetComponentByClass(UMeshComponent::StaticClass()));


	if(SplineComponent)
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("bCanPatrol"), true);
	}
	else
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("bCanPatrol"), false);
	}

	// WalkSpeed = 300;



}

// Called every frame
void ABase_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABase_Monster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

