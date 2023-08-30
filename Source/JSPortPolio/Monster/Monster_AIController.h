// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Monster_AIController.generated.h"

/**
 * 
 */
UCLASS()
class JSPORTPOLIO_API AMonster_AIController : public AAIController
{
	GENERATED_BODY()

	AMonster_AIController();

	void OnPossess(APawn* _InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent* BlackboardComponent;

	
public:
	FORCEINLINE class UBehaviorTreeComponent* GetBehaviorTreeComponent()
	{
		return BehaviorTreeComponent;
	}

	FORCEINLINE class UBlackboardComponent* GetBlackboardComponent()
	{
		return BlackboardComponent;
	}



	
};
