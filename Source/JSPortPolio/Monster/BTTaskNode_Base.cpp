// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Base.h"
#include  <Datas/CharacterDatas.h>
#include "Character_Base.h"
#include "Monster/MonsterAnimInstance.h"

UBTTaskNode_Base::UBTTaskNode_Base()
{

	bNotifyTick = true;
}



void UBTTaskNode_Base::OnGameplayTaskActivated(class UGameplayTask& Task)
{
	

}

void UBTTaskNode_Base::SetAnim()
{


}

ACharacter_Base* UBTTaskNode_Base::GetBaseCharacter(UBehaviorTreeComponent& OwnerComp)
{
	AMonster_AIController* AiCon = OwnerComp.GetOwner<AMonster_AIController>();
	if (nullptr == AiCon || false == AiCon->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	ACharacter_Base* Character = AiCon->GetPawn<ACharacter_Base>();

	if (nullptr == Character || false == Character->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return Character;
}