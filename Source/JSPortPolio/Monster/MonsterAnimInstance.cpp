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

	AniState = Chracter->GetAnistate();

	UAnimMontage* Montage = MonsterAnimations[AniState];
	
	if (nullptr == Montage)
	{
		return;
	}
	
	// 조건1. 몽타주 재생이 끝났다.
	// 조건2. 이전에 이미 재생한 몽타주다.
	// 조건3. 몽타주가 루프다.
	if (false == Montage_IsPlaying(Montage))
	{
		//if (Montage == CurMontage && -1 != DefaultAniState && false == Montage->bLoop)
		//{
		//	Montage = AllAnimations[DefaultAniState];
		//}
		Montage_Play(Montage, 1.0f);
	}

}




void UMonsterAnimInstance::MontageEnd(UAnimMontage* Anim, bool _Inter)
{

}