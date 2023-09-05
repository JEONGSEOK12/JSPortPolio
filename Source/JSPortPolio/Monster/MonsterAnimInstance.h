// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Monster_Enums.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class JSPORTPOLIO_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UMonsterAnimInstance();

	void NativeBeginPlay();

	void NativeUpdateAnimation(float _DeltaTime) override;

	UFUNCTION()
	void MontageEnd(UAnimMontage* Anim, bool _Inter);
public:

	Monster_Enum* MonsterAnim;
	
	//TMap<int, UAnimMontage*> MonsterAnimations;

	//int AniState = 0;
public:


};
