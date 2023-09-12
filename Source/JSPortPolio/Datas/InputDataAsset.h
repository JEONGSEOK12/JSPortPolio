// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class JSPORTPOLIO_API UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditdefaultsOnly,BlueprintReadOnly)
	UInputAction* MoveForward;
	
	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveRight;

	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveTurn;

	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly)
	UInputAction* Jump;

	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly)
	UInputAction* CameraReset;

	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveMouse;

};
