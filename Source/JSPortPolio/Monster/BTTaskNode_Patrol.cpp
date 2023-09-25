// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Patrol.h"
#include "Monster_Enums.h"
#include "Monster/Base_Monster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include <Monster/Base_Monster.h>



EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetBaseCharacter(OwnerComp)->SetAniState(Monster_Enum::Patrol);

	// GetBaseCharacter(OwnerComp)->SetActorLocation();

	UBlackboardComponent* Blackboard = GetBaseCharacter(OwnerComp)->GetBlackboardComponent();

	FVector BaseLocation = Blackboard->GetValueAsVector(TEXT("BaseLocation"));

	GetBaseCharacter(OwnerComp)->SetActorLocation(BaseLocation);

	GetBaseCharacter(OwnerComp)->SetActorRotation(FRotator(0, 0, 0));

	return EBTNodeResult::InProgress;
}


void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	DeathCheck(OwnerComp);

	ABase_Monster* Monster = GetBaseMonster(OwnerComp);
	UBlackboardComponent* Blackboard = Monster->GetBlackboardComponent();
	USkeletalMeshComponent* Mesh = Monster->Mesh;
	USplineComponent* SplineComponent = Monster->SplineComponent;
	float PatrolDistance = Blackboard->GetValueAsFloat(TEXT("PatrolDistance"));


	Blackboard->SetValueAsFloat(TEXT("PatrolDistance"), PatrolDistance + GetBaseCharacter(OwnerComp)->CharacterData->WalkSpeed * DelataSeconds);

	FTransform Transform = SplineComponent->GetTransformAtDistanceAlongSpline(PatrolDistance, ESplineCoordinateSpace::Local);

	Transform.SetScale3D(Mesh->GetComponentScale());

	Transform.SetRotation(Transform.GetRotation() * FQuat(FVector(0, 0, 1), FMath::DegreesToRadians(-90)));

	Mesh->SetRelativeTransform(Transform);

	if (SplineComponent->IsClosedLoop() && SplineComponent->GetSplineLength() <= PatrolDistance)
	{
		Blackboard->SetValueAsFloat(TEXT("PatrolDistance"), 0);
	}


	AActor* Target = TrackRangeCheck(OwnerComp);
	if (Target)
	{
		FRotator MeshRot = Mesh->GetComponentRotation();

		Monster->SetActorLocation(Mesh->GetComponentLocation());
		Monster->SetActorRotation(MeshRot);

		Mesh->SetRelativeLocation(FVector(0,0,0));
		Mesh->SetRelativeRotation(FRotator(0, -90, 0));


		Blackboard->SetValueAsVector(TEXT("RunLastLocation"), GetBaseCharacter(OwnerComp)->GetActorLocation());
		SetStateChange(OwnerComp, (uint8)Monster_Enum::Run);
		return;
	}


}




