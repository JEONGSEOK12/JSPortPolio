// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Return.h"
#include <Monster/Base_Monster.h>
#include "Components/SplineComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Character_Base.h"
#include <Datas/CharacterDatas.h>



EBTNodeResult::Type UBTTaskNode_Return::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetBaseCharacter(OwnerComp)->SetAniState(Monster_Enum::Walk);

	return EBTNodeResult::InProgress;
}


void UBTTaskNode_Return::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);


	UBlackboardComponent* Blackboard = GetBaseCharacter(OwnerComp)->GetBlackboardComponent();

	float PatrolDistance = Blackboard->GetValueAsFloat(TEXT("PatrolDistance"));

	FTransform Transform = GetBaseMonster(OwnerComp)->SplineComponent->GetTransformAtDistanceAlongSpline(PatrolDistance, ESplineCoordinateSpace::Local);
	
	//네비 시스템으로 트랜스폼으로 이동

	FVector ReturnLocation = Blackboard->GetValueAsVector(TEXT("RunLastLocation"));

	UNavigationPath* NewPath = FindNavPath(OwnerComp, ReturnLocation);
	
	if (!NewPath)
	{
		CharacterMove(OwnerComp, NewPath->PathPoints[1], DelataSeconds,GetBaseCharacter(OwnerComp)->CharacterData->WalkSpeed);
	}


	FVector Dis = GetBaseCharacter(OwnerComp)->GetActorLocation() - ReturnLocation;
	if (Dis.Size() <= 30.f)
	{
		SetStateChange(OwnerComp, Monster_Enum::Idle);
		return;
	}

}