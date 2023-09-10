// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Base.h"
#include  <Datas/CharacterDatas.h>
#include "Character_Base.h"
#include "Monster/MonsterAnimInstance.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "Character_Base.h"


UBTTaskNode_Base::UBTTaskNode_Base()
{

	bNotifyTick = true;
}



void UBTTaskNode_Base::OnGameplayTaskActivated(class UGameplayTask& Task)
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

void UBTTaskNode_Base::SetStateChange(UBehaviorTreeComponent& OwnerComp, uint8 _State)
{
	UBlackboardComponent* BlockBoard = OwnerComp.GetBlackboardComponent();

	if (nullptr == BlockBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
		return;
	}

	BlockBoard->SetValueAsEnum(TEXT("Monster_Enum"), _State);

	FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
}