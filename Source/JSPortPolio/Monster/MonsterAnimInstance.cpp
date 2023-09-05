// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAnimInstance.h"
#include "Monster/BTTaskNode_Base.h"
#include  <Datas/CharacterDatas.h>
#include "Character_Base.h"
#include "Monster_Enums.h"


UMonsterAnimInstance::UMonsterAnimInstance()
{
	
}


void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageEnded.AddDynamic(this, &UMonsterAnimInstance::MontageEnd);
	

}

void UMonsterAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	Super::NativeUpdateAnimation(_DeltaTime);

	ACharacter_Base* Chracter = Cast<ACharacter_Base>(GetOwningActor());

	
	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	
	if(Chracter->GetAniState() !=0)
	{
		UAnimMontage* Montage = Chracter->AllAnimations[Chracter->GetAniState()];

		if (nullptr == Montage)
		{
			return;
		}

		if (false == Montage_IsPlaying(Montage))
		{

			Montage_Play(Montage, 1.0f);
		}

	}

	

}




void UMonsterAnimInstance::MontageEnd(UAnimMontage* Anim, bool _Inter)
{

}