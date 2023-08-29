// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAnimInstance.h"



UMonsterAnimInstance::UMonsterAnimInstance()
{
	this->SetAnimationDelegate.AddDynamic(this, &TestFunc);
}




void UMonsterAnimInstance::TestFunc(Monster_Enum Test)
{

}