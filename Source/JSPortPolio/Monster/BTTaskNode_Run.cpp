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

	// ACharacter_Base* CharacterBase = GetBaseCharacter(OwnerComp);

	AActor* Target = TrackRangeCheck(OwnerComp);
	//타겟이 없으면 리턴
	if (Target==nullptr)
	{
		SetStateChange(OwnerComp, (uint8)Monster_Enum::Return);
		return;
	}
	
	FVector TargetLocation = Target->GetActorLocation();

	FVector LastLocation = BlackBoard->GetValueAsVector(TEXT("TargetLastLocation"));


	if (abs(TargetLocation.X - LastLocation.X) >= 10 || abs(TargetLocation.Y != LastLocation.Y) >= 10)
	{
		
		// UNavigationPath* TestPath = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), CharacterBase->GetActorLocation(), TargetLocation);

		UNavigationPath* NewPath = FindNavPath(OwnerComp, TargetLocation);
		BlackBoard->SetValueAsVector(TEXT("TargetLastLocation"), TargetLocation);
		BlackBoard->SetValueAsObject(TEXT("NavPath"), NewPath);

	}

	UObject* NavObject = BlackBoard->GetValueAsObject(TEXT("NavPath"));
	UNavigationPath* NavPath = Cast<UNavigationPath>(NavObject);
	

	//길못찾음
	if (nullptr == NavPath || true == NavPath->PathPoints.IsEmpty())
	{
		SetStateChange(OwnerComp, (uint8)Monster_Enum::Return);
		return;
	}


	FVector FowardLocation;
	FowardLocation = NavPath->PathPoints[1];
	
	FVector MyLocation = GetBaseCharacter(OwnerComp)->GetActorLocation();

	FowardLocation.Z = 0;
	MyLocation.Z = 0;

	FVector TargetDir = FowardLocation - MyLocation;
	TargetDir.Normalize();

	float RunSpeed = GetBaseCharacter(OwnerComp)->CharacterData->RunSpeed;

	float ForX = FowardLocation.X;
	float ForY = FowardLocation.Y;

	float MyX = MyLocation.X;
	float MyY = MyLocation.Y;

	float TarX = TargetDir.X;
	float TarY = TargetDir.Y;

	float Tett = GetBaseCharacter(OwnerComp)->fTest;

	if(Tett>1)
	{
		// GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("For X : %f , Y :%f "), ForX,ForY));
		// GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("My X : %f , Y : %f"), MyX, MyY));
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("TarX : %f,TarY : %f"), TargetDir.X, TargetDir.Y));
		
		
		GetBaseCharacter(OwnerComp)->fTest = 0;
	}
	else
	{
		GetBaseCharacter(OwnerComp)->fTest += DelataSeconds;
	}

	GetBaseCharacter(OwnerComp)->MoveCharacter(TargetDir, RunSpeed);

}