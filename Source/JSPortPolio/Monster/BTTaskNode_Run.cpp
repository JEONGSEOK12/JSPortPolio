// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Run.h"
#include "Character_Base.h"
#include <Monster/Monster_Enums.h>

EBTNodeResult::Type UBTTaskNode_Run::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	GetBaseCharacter(OwnerComp)->SetAniState(Monster_Enum::Run);


	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Run::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	DeathCheck(OwnerComp);








}