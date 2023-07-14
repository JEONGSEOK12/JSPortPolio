// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stage_Plane.generated.h"

UCLASS()
class JSPORTPOLIO_API AStage_Plane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStage_Plane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};