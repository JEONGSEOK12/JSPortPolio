// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Return.h"
#include <Monster/Base_Monster.h>
#include "Components/SplineComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTaskNode_Return::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	return EBTNodeResult::InProgress;
}


void UBTTaskNode_Return::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);


	UBlackboardComponent* Blackboard = GetBaseCharacter(OwnerComp)->GetBlackboardComponent();

	float PatrolDistance = Blackboard->GetValueAsFloat(TEXT("PatrolDistance"));

	FTransform Transform = GetBaseMonster(OwnerComp)->SplineComponent->GetTransformAtDistanceAlongSpline(PatrolDistance, ESplineCoordinateSpace::Local);
	
	//�׺� �ý������� Ʈ���������� �̵�




}