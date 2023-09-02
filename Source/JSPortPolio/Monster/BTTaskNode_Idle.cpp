// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Idle.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "Character_Base.h"
#include "Monster/MonsterAnimInstance.h"




EBTNodeResult::Type UBTTaskNode_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMonster_AIController* AICon = OwnerComp.GetOwner<AMonster_AIController>();

	ACharacter_Base* Ch = AICon->OwnerBase;

	
	
	Ch->TaskIdle = this;

	if (SetAnimationDelegate.IsBound() == false)
	{
		Ch->BindAnim1();
	}
	//UAnimInstance* AnimInst = Ch->GetMesh()->GetAnimInstance();

	//UMonsterAnimInstance* MyAnimInst = Cast<UMonsterAnimInstance>(AnimInst);

	if (SetAnimationDelegate.IsBound() == true)
	{
		SetAnimationDelegate.Broadcast(Monster_Enum::Idle);
	}






	return EBTNodeResult::Failed;Áö}


void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	
}