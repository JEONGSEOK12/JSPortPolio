// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Patrol.h"






EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}


void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{

}




