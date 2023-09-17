// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Return.h"

EBTNodeResult::Type UBTTaskNode_Return::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	return EBTNodeResult::InProgress;
}


void UBTTaskNode_Return::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

}