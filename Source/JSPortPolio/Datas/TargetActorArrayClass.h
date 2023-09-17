// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TargetActorArrayClass.generated.h"

/**
 * 
 */
UCLASS()
class JSPORTPOLIO_API UTargetActorArrayClass : public UObject
{
public:
	GENERATED_BODY()
	
	TArray<AActor*> TargetActorArray;
};
