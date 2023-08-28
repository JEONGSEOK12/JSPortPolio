// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Monster_BTTaskNode_Walk.generated.h"

/**
 * 
 */
UCLASS()
class JSPORTPOLIO_API UMonster_BTTaskNode_Walk : public UBTTaskNode
{
	GENERATED_BODY()

	void OnGameplayTaskActivated(class UGameplayTask&) override;

	
};
