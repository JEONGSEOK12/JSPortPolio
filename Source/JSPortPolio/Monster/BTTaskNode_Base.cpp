// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskNode_Base.h"
#include  <Datas/CharacterDatas.h>
#include "Character_Base.h"

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

	Skel->GetAnimInstance();

}

void UBTTaskNode_Base::SetAnim()
{


}
