// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Select/Stage_Plane.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AStage_Plane::AStage_Plane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStage_Plane::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStage_Plane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

