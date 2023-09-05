// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Base.h"
#include "MyGameInstance.h"
#include "Engine/DataTable.h"
#include "Datas/CharacterDatas.h"
#include "Monster/MonsterAnimInstance.h"



// Sets default values
ACharacter_Base::ACharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacter_Base::BeginPlay()
{
	Super::BeginPlay();


	UMyGameInstance* Inst = GetWorld()->GetGameInstance<UMyGameInstance>();


	this;

	if (nullptr != Inst)
	{
		CharacterData = Inst->GetCharacterData(DataName);
	}

	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();


	UMonsterAnimInstance* MonsterAnimInstance = Cast<UMonsterAnimInstance>(AnimInst);

	// MonsterAnimInstance->MonsterAnimations = CharacterData->AllAnimations;
	 for (TPair<int, UAnimMontage*> Pair : CharacterData->AllAnimations)
	 {
		 AllAnimations.Add(Pair.Key, Pair.Value);
	 
	 }

	 GetActorLocation();



	
}



// Called every frame
void ACharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


UBehaviorTree* ACharacter_Base::GetBehaviorTree()
{
	return CharacterData->BehaviorTree;
};





