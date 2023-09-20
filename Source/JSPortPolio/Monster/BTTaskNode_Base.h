// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskNode_Base.generated.h"

/**
 * 
 */


UCLASS()
class JSPORTPOLIO_API UBTTaskNode_Base : public UBTTask_BlackboardBase
{
	GENERATED_BODY()


public:

	UBTTaskNode_Base();


	void OnGameplayTaskActivated(class UGameplayTask& Task) override;

	
	class ACharacter_Base* GetBaseCharacter(UBehaviorTreeComponent& OwnerComp);

	class ABase_Monster* GetBaseMonster(UBehaviorTreeComponent& OwnerComp);

	void SetStateChange(UBehaviorTreeComponent& OwnerComp, uint8 _State);

	template<typename EnumType>
	void SetStateChange(UBehaviorTreeComponent& OwnerComp, EnumType _State)
	{
		SetStateChange(OwnerComp, static_cast<uint8>(_State));
	}

	void DeathCheck(UBehaviorTreeComponent& OwnerComp);

	AActor* TrackRangeCheck(UBehaviorTreeComponent& OwnerComp);

	class UNavigationPath* FindNavPath(UBehaviorTreeComponent& OwnerComp, AActor* _Actor);

	class UNavigationPath* FindNavPath(UBehaviorTreeComponent& _OwnerComp, FVector _EndPos);




};
