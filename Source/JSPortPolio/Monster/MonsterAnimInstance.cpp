// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAnimInstance.h"
#include "Monster/BTTaskNode_Base.h"
#include  <Datas/CharacterDatas.h>
#include "Character_Base.h"



UMonsterAnimInstance::UMonsterAnimInstance()
{
	
}


void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	
	TaskNode->SetAnimationDelegate.AddDynamic(this, &UMonsterAnimInstance::TestFunc);


}



void UMonsterAnimInstance::TestFunc(Monster_Enum Test)
{


	ACharacter_Base* Chracter = Cast<ACharacter_Base>(GetOwningActor());

	Montage_Play(Chracter->CharacterData->AllAnimations[Test]);


	//Montage_Play();
}