// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class JSPORTPOLIO_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	UPlayerAnimInstance();

	void NativeBeginPlay();

	void NativeUpdateAnimation(float _DeltaTime) override;

	UFUNCTION()
	void MontageEnd(UAnimMontage* Anim, bool _Inter);
	
};
