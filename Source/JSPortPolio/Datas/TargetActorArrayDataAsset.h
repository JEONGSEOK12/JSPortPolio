// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TargetActorArrayDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class JSPORTPOLIO_API UTargetActorArrayDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	TArray<AActor*> TargetActorArr;

};
