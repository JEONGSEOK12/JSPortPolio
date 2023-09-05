// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Walk.h"
#include "Character_Base.h"





EBTNodeResult::Type UBTTaskNode_Walk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	GetBaseCharacter(OwnerComp)->SetAniState(Monster_Enum::Walk);

	return 	EBTNodeResult::InProgress;
}


void UBTTaskNode_Walk::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{

}