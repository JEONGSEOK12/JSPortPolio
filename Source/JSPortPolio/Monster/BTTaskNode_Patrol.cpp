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
	DeathCheck(OwnerComp);

	UBlackboardComponent* Blackboard = GetBaseCharacter(OwnerComp)->GetBlackboardComponent();

	float PatrolDistance = Blackboard->GetValueAsFloat(TEXT("PatrolDistance"));

	Blackboard->SetValueAsFloat(TEXT("PatrolDistance"), PatrolDistance + GetBaseMonster(OwnerComp)->WalkSpeed * DelataSeconds);

	FTransform Transform = GetBaseMonster(OwnerComp)->SplineComponent->GetTransformAtDistanceAlongSpline(PatrolDistance, ESplineCoordinateSpace::Local);

	Transform.SetScale3D(GetBaseMonster(OwnerComp)->MeshComponent->GetComponentScale());

	Transform.SetRotation(Transform.GetRotation() * FQuat(FVector(0, 0, 1), FMath::DegreesToRadians(-90)));

	GetBaseMonster(OwnerComp)->MeshComponent->SetRelativeTransform(Transform);

	if (GetBaseMonster(OwnerComp)->SplineComponent->IsClosedLoop() && GetBaseMonster(OwnerComp)->SplineComponent->GetSplineLength() <= PatrolDistance)
	{
		Blackboard->SetValueAsFloat(TEXT("PatrolDistance"), 0);
	}

}




