// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Base.h"
#include "Character_Base.h"


UBTTaskNode_Base::UBTTaskNode_Base()
{

	bNotifyTick = true;
}


void UBTTaskNode_Base::OnGameplayTaskActivated(class UGameplayTask& Task)
{

	


	// CH = Cast<ACharacter_Base>(Task.GetOwnerActor());
	// CH->TaskBase = this;

	
}

void UBTTaskNode_Base::SetAnim()
{


}
