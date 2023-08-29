// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/BTTaskNode_Base.h"
#include "BTTaskNode_Idle.generated.h"

/**
 * 
 */
UCLASS()
class JSPORTPOLIO_API UBTTaskNode_Idle : public UBTTaskNode_Base
{
	GENERATED_BODY()

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds);
	
};
