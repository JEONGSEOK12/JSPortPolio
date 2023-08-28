// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Base_Monster.h"
#include "MyGameInstance.h"
#include "Engine/DataTable.h"
#include <Datas/MonsterDatas.h>


// Sets default values
ABase_Monster::ABase_Monster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABase_Monster::BeginPlay()
{
	Super::BeginPlay();


	UMyGameInstance* Inst = GetWorld()->GetGameInstance<UMyGameInstance>();


	if (nullptr != Inst)
	{
		MonsterData = Inst->GetMonsterData(DataName);



	}
	
}

// Called every frame
void ABase_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABase_Monster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

