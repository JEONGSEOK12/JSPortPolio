// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Idle.h"
#include <BehaviorTree/BlackboardComponent.h>



EBTNodeResult::Type UBTTaskNode_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMonster_AIController* AICon = OwnerComp.GetOwner<AMonster_AIController>();

	AICon->GetBehaviorTreeComponent();



	return EBTNodeResult::Succeeded;
}


void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	
}