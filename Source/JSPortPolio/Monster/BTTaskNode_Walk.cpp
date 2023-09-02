// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Walk.h"
#include "Character_Base.h"





EBTNodeResult::Type UBTTaskNode_Walk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMonster_AIController* AICon = OwnerComp.GetOwner<AMonster_AIController>();

	ACharacter_Base* Ch = AICon->OwnerBase;



	Ch->TaskWalk = this;


	if (SetAnimationDelegate.IsBound() == false)
	{
		Ch->BindAnim2();
	}

	SetAnimationDelegate.Broadcast(Monster_Enum::Walk);


	return 	EBTNodeResult::InProgress;
}


void UBTTaskNode_Walk::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{

}