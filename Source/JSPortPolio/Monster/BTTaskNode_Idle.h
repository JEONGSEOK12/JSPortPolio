// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/BTTaskNode_Base.h"
#include "Character_Base.h"
#include "BTTaskNode_Idle.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetAnimSignature1, Monster_Enum, Test);



UCLASS()
class JSPORTPOLIO_API UBTTaskNode_Idle : public UBTTaskNode_Base
{

public:
	GENERATED_BODY()

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds);

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FSetAnimSignature1 SetAnimationDelegate;

	

};
