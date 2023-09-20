// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Idle.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "Character_Base.h"
#include "Monster_Enums.h"
#include "Monster/Base_Monster.h"




EBTNodeResult::Type UBTTaskNode_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetBaseCharacter(OwnerComp)->SetAniState(Monster_Enum::Idle);

	if(!OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("BaseLocationCheck")))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("BaseLocation"), GetBaseCharacter(OwnerComp)->GetActorLocation());
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("BaseLocationCheck"), true);
	}

	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetObject"), nullptr);
	
	ABase_Monster* Monster = Cast<ABase_Monster>(GetBaseCharacter(OwnerComp));
	
	if (GetBaseMonster(OwnerComp)->bPatrol)
	{

		//ExecuteTask���� FinishLatentTask �ᵵ �Ǵ��� ���߿� Ȯ��
		SetStateChange(OwnerComp, (uint8)Monster_Enum::Patrol);
		return EBTNodeResult::Failed;
	}





	return EBTNodeResult::InProgress;

}


void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{

	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	DeathCheck(OwnerComp);



	
}

