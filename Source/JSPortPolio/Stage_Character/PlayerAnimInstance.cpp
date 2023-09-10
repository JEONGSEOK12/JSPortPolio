// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Character/PlayerAnimInstance.h"
#include "Character_Base.h"
#include <Monster/Monster_Enums.h>


UPlayerAnimInstance::UPlayerAnimInstance()
{

}


void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageEnded.AddDynamic(this, &UPlayerAnimInstance::MontageEnd);


}

void UPlayerAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	Super::NativeUpdateAnimation(_DeltaTime);

	ACharacter_Base* Chracter = Cast<ACharacter_Base>(GetOwningActor());


	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}


	if (Chracter->GetAniState() != 0)
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




void UPlayerAnimInstance::MontageEnd(UAnimMontage* Anim, bool _Inter)
{

}