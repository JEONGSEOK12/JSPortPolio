// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Patrol.h"
#include "Monster_Enums.h"
#include "Monster/Base_Monster.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BlackboardComponent.h"




EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetBaseCharacter(OwnerComp)->SetAniState(Monster_Enum::Patrol);

	return EBTNodeResult::InProgress;
}


void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	UBlackboardComponent* Blackboard = GetBaseCharacter(OwnerComp)->GetBlackboardComponent();

	float PatrolDistance = Blackboard->GetValueAsFloat(TEXT("PatrolDistance"));

	Blackboard->SetValueAsFloat(TEXT("PatrolDistance"), PatrolDistance + GetBaseMonster(OwnerComp)->WalkSpeed * DelataSeconds);
	
	FTransform Transform = GetBaseMonster(OwnerComp)->SplineComponent->GetTransformAtDistanceAlongSpline(PatrolDistance,ESplineCoordinateSpace::Local);



	GetBaseMonster(OwnerComp)->MeshComponent->SetRelativeLocation(Transform.GetLocation());
	



}




