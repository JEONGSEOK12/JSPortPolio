// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Patrol.h"
#include "Monster_Enums.h"
#include "Character_Base.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"





EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetBaseCharacter(OwnerComp)->SetAniState(Monster_Enum::Patrol);
	GetBaseCharacter(OwnerComp)->GetCharacterMovement();

	return EBTNodeResult::InProgress;
}


void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	//GetBaseCharacter(OwnerComp)->GetMovementComponent()->Getcharactermove
	

}




