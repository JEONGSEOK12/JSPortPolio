// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "MyGameInstance.h"
#include "Character_Base.h"


AMonster_AIController::AMonster_AIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));;

}



void AMonster_AIController::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);

	if (nullptr != BehaviorTreeComponent && true == BehaviorTreeComponent->IsValidLowLevel())
	{


		

		 ACharacter_Base* AIPawn = Cast<ACharacter_Base>(_InPawn);

		 UMyGameInstance* Inst = GetWorld()->GetGameInstance<UMyGameInstance>();


		 if (nullptr != Inst)
		 {
			 AIPawn->CharacterData = Inst->GetCharacterData(AIPawn->DataName);
		 }

		 
		  UBehaviorTree* BehaviorTree = AIPawn->GetBehaviorTree();
		  
		  if (nullptr == BehaviorTree || false == BehaviorTree->IsValidLowLevel())
		  {
		  	UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BehaviorTree || false == BehaviorTree->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		  	return;
		  }
		  
		  BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		  
		  BehaviorTreeComponent->StartTree(*BehaviorTree);
	}
}