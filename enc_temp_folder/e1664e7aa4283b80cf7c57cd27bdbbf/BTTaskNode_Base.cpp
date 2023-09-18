// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Base.h"
#include "Monster/Base_Monster.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <Monster/Monster_AIController.h>
#include "Monster_Enums.h"


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

ABase_Monster* UBTTaskNode_Base::GetBaseMonster(UBehaviorTreeComponent& OwnerComp)
{
	AMonster_AIController* AiCon = OwnerComp.GetOwner<AMonster_AIController>();
	if (nullptr == AiCon || false == AiCon->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	ABase_Monster* Monster = AiCon->GetPawn<ABase_Monster>();

	if (nullptr == Monster || false == Monster->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return Monster;
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

void UBTTaskNode_Base::DeathCheck(UBehaviorTreeComponent& OwnerComp)
{
	if (GetBaseCharacter(OwnerComp)->HP <= 0)
	{

	

		SetStateChange(OwnerComp, (uint8)Monster_Enum::Death);
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
	}
	
}

void UBTTaskNode_Base::TrackRangeCheck(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* BlockBoard = OwnerComp.GetBlackboardComponent();

	BlockBoard->GetValueAsFloat(TEXT("TrackRange"));
	BlockBoard->GetValueAsObject(TEXT("TargetObject"));




}










