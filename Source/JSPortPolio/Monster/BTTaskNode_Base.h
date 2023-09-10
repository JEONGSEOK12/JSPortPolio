// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Monster/Monster_AIController.h"
#include <Monster/Monster_Enums.h>
#include "BTTaskNode_Base.generated.h"



/**
 * 
 */




UCLASS()
class JSPORTPOLIO_API UBTTaskNode_Base : public UBTTask_BlackboardBase
{
	GENERATED_BODY()


public:

	UBTTaskNode_Base();


	void OnGameplayTaskActivated(class UGameplayTask& Task) override;

	
	class ACharacter_Base* GetBaseCharacter(UBehaviorTreeComponent& OwnerComp);

	void SetStateChange(UBehaviorTreeComponent& OwnerComp, uint8 _State);


};
