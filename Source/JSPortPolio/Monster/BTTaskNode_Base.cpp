// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Base.h"
#include "Monster/Base_Monster.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <Monster/Monster_AIController.h>
#include "Monster_Enums.h"
#include "Character_Base.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

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
		return;
	}
	
}

AActor* UBTTaskNode_Base::TrackRangeCheck(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

	TArray<AActor*> TargetActors;
	TargetActors = GetBaseCharacter(OwnerComp)->TargetArray;

	float SearchRange = GetBaseCharacter(OwnerComp)->CharacterData->TrackRange;
	AActor* ResultActor = nullptr;

	if (0 != TargetActors.Num())
	{
		float Range = TNumericLimits<float>::Max();

		for (AActor* Target :TargetActors)
		{
			float Dis = (GetBaseCharacter(OwnerComp)->Mesh->GetComponentLocation() - Target->GetActorLocation()).Size();

			if (SearchRange <= Dis)
			{
				continue;
			}

			if (Range > Dis)
			{
				Range = Dis;
				ResultActor = Target;
			}
		}
	}

	return ResultActor;

}



UNavigationPath* UBTTaskNode_Base::FindNavPath(UBehaviorTreeComponent& OwnerComp, AActor* Actor)
{
	return FindNavPath(OwnerComp, Actor->GetActorLocation());
}

UNavigationPath* UBTTaskNode_Base::FindNavPath(UBehaviorTreeComponent& OwnerComp, FVector EndPos)
{

	UNavigationPath* PathObject = nullptr;
	FVector StartPos = GetBaseCharacter(OwnerComp)->GetActorLocation();

	PathObject = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), StartPos, EndPos);

	return PathObject;
}

void UBTTaskNode_Base::CharacterMove(UBehaviorTreeComponent& OwnerComp, FVector TargetLocation, float DeltaSeconds ,float Speed)
{

	FVector MyLocation = GetBaseCharacter(OwnerComp)->GetActorLocation();
	// FVector Dir = TargetLocation - MyLocation;
	// Dir.Normalize();
	// 
	// FVector OtherForward = GetBaseCharacter(OwnerComp)->GetActorForwardVector();
	// OtherForward.Normalize();
	// 
	// Dir.Z = 0;
	// OtherForward.Z = 0;
	// 
	// FVector Cross = FVector::CrossProduct(OtherForward, Dir);
	// 
	// float Angle0 = Dir.Rotation().Yaw;
	// float Angle1 = OtherForward.Rotation().Yaw;
	// 
	// if (FMath::Abs(Angle0 - Angle1) >= 10.0f)
	// {
	// 	FRotator Rot = FRotator::MakeFromEuler({ 0, 0, Cross.Z * 500.0f * DeltaSeconds });
	// 	GetBaseCharacter(OwnerComp)->AddActorWorldRotation(Rot);
	// }
	// else 
	// {
	// 	FRotator Rot = Dir.Rotation();
	// 	GetBaseCharacter(OwnerComp)->SetActorRotation(Rot);
	// }
	// 
	// FVector MoveDir = Dir * Speed;






	FQuat MyQuat = GetBaseCharacter(OwnerComp)->GetActorQuat();
	FVector Dir = TargetLocation - MyLocation;
	Dir.Normalize();
	FQuat RotQuat(Dir, 0);
	GetBaseCharacter(OwnerComp)->SetActorRotation(RotQuat);


	// GetBaseCharacter(OwnerComp)->AddMovementInput(MoveDir);



}




