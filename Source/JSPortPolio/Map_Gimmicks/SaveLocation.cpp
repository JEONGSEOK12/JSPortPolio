// Fill out your copyright notice in the Description page of Project Settings.


#include "Map_Gimmicks/SaveLocation.h"

// Sets default values
ASaveLocation::ASaveLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASaveLocation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASaveLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

