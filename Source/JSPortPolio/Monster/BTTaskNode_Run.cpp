// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Run.h"
#include "Character_Base.h"
#include <Datas/CharacterDatas.h>
#include <Monster/Monster_Enums.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"





EBTNodeResult::Type UBTTaskNode_Run::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	GetBaseCharacter(OwnerComp)->SetAniState(Monster_Enum::Run);


	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Run::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	DeathCheck(OwnerComp);

	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

	AActor* Target = TrackRangeCheck(OwnerComp);
	//Ÿ���� ������ ����
	if (Target==nullptr)
	{
		SetStateChange(OwnerComp, (uint8)Monster_Enum::Return);
		return;
	}
	
	FVector TargetLocation = Target->GetActorLocation();

	FVector LastLocation = BlackBoard->GetValueAsVector(TEXT("TargetLastLocation"));


	if(TargetLocation != LastLocation)
	{
		
		UNavigationPath* NewPath = FindNavPath(OwnerComp, TargetLocation);
		BlackBoard->SetValueAsVector(TEXT("TargetLastLocation"), TargetLocation);
		BlackBoard->SetValueAsObject(TEXT("NavPath"), NewPath);

	}

	UObject* NavObject = BlackBoard->GetValueAsObject(TEXT("NavPath"));
	UNavigationPath* NavPath = Cast<UNavigationPath>(NavObject);
	
	//���ã��
	if (nullptr == NavPath)
	{
		SetStateChange(OwnerComp, (uint8)Monster_Enum::Return);
		return;
	}

	//���ã��2
	if (nullptr != NavPath && true == NavPath->PathPoints.IsEmpty())
	{
		SetStateChange(OwnerComp, (uint8)Monster_Enum::Return);
		return;
	}


	FVector FowardLocation;
	if (nullptr != NavPath)
	{
		FowardLocation = NavPath->PathPoints[1];
	}

	

	CharacterMove(OwnerComp, FowardLocation, DelataSeconds, GetBaseCharacter(OwnerComp)->CharacterData->RunSpeed);


}