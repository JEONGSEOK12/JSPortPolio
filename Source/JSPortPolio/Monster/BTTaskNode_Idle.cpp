// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Idle.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "Character_Base.h"
#include "Monster/MonsterAnimInstance.h"


EBTNodeResult::Type UBTTaskNode_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMonster_AIController* AICon = OwnerComp.GetOwner<AMonster_AIController>();

	ACharacter_Base* Ch = AICon->OwnerBase;

	
	

	
	UAnimInstance* AnimInst = Ch->GetMesh()->GetAnimInstance();

	UMonsterAnimInstance* MyAnimInst = Cast<UMonsterAnimInstance>(AnimInst);

	MyAnimInst->TaskNode = this;

	


	SetAnimationDelegate.Broadcast(Monster_Enum::Idle);







	return EBTNodeResult::Succeeded;
}


void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	
}