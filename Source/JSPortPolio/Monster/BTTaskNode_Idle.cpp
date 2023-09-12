// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Idle.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "Character_Base.h"
#include "Monster_Enums.h"




EBTNodeResult::Type UBTTaskNode_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetBaseCharacter(OwnerComp)->SetAniState(Monster_Enum::Idle);

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetObject"), nullptr);



	return EBTNodeResult::InProgress;

}


void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{

	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	DeathCheck(OwnerComp);

	FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);

}

