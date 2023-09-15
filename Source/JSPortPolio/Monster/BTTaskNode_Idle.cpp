// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Idle.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "Character_Base.h"
#include "Monster_Enums.h"
#include "Monster/Base_Monster.h"




EBTNodeResult::Type UBTTaskNode_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetBaseCharacter(OwnerComp)->SetAniState(Monster_Enum::Idle);


	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetObject"), nullptr);
	
	ABase_Monster* Monster = Cast<ABase_Monster>(GetBaseCharacter(OwnerComp));
	
	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("bCanPatrol")))
	{
		//ExecuteTask에서 FinishLatentTask 써도 되는지 나중에 확인
		SetStateChange(OwnerComp, (uint8)Monster_Enum::Patrol);
	}
	else
	{
		return EBTNodeResult::InProgress;
	}




	return EBTNodeResult::InProgress;

}


void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{

	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	DeathCheck(OwnerComp);



	
}

