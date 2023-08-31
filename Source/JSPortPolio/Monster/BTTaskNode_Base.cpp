// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Base.h"
#include  <Datas/CharacterDatas.h>
#include "Character_Base.h"
#include "Monster/MonsterAnimInstance.h"

UBTTaskNode_Base::UBTTaskNode_Base()
{

	bNotifyTick = true;
}



void UBTTaskNode_Base::OnGameplayTaskActivated(class UGameplayTask& Task)
{

	
	Ch = Cast<ACharacter_Base>(Task.GetOwnerActor());

	Ch->CharacterData;

	class UActorComponent* Comp = Ch->GetComponentByClass(USkeletalMeshComponent::StaticClass());

	USkeletalMeshComponent* Skel = Cast<USkeletalMeshComponent>(Comp);

	

	UMonsterAnimInstance* AnimInst = Cast<UMonsterAnimInstance>(Skel->GetAnimInstance());


	SetAnimationDelegate.Broadcast(Monster_Enum::Scream);


}

void UBTTaskNode_Base::SetAnim()
{


}
