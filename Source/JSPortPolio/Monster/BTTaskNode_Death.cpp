// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Death.h"
#include "Character_Base.h"
#include "Monster_Enums.h"



EBTNodeResult::Type UBTTaskNode_Death::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetBaseCharacter(OwnerComp)->SetAniState(Monster_Enum::Death);
	
	CurAni = GetBaseCharacter(OwnerComp)->AniState;
	DeathTime = GetBaseCharacter(OwnerComp)->AllAnimations[CurAni]->CalculateSequenceLength();



	return EBTNodeResult::InProgress;

}


void UBTTaskNode_Death::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{

	Curtime += DelataSeconds;

	if (DeathTime < Curtime)
	{
		GetBaseCharacter(OwnerComp)->Destroy();
	}


}








