// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAnimInstance.h"
#include "Monster/BTTaskNode_Base.h"
#include  <Datas/CharacterDatas.h>



UMonsterAnimInstance::UMonsterAnimInstance()
{
	
}


void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();


}



void UMonsterAnimInstance::TestFunc(Monster_Enum Test)
{

	//Montage_Play(Ch->CharacterData->AllAnimations[Test]);
}