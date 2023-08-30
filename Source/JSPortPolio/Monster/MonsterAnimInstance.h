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


	void TestFunc(Monster_Enum Test);


	TMap<Monster_Enum, class UAnimMontage*> AllAnimations;
	
};
