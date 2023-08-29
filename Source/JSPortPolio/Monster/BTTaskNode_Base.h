// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Monster/Monster_AIController.h"
#include "BTTaskNode_Base.generated.h"

/**
 * 
 */
UCLASS()
class JSPORTPOLIO_API UBTTaskNode_Base : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UBTTaskNode_Base();

	void OnGameplayTaskActivated(class UGameplayTask&) override;

	

};
