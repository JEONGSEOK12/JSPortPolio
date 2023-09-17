// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Base.h"
#include "MyGameInstance.h"
#include "Engine/DataTable.h"
#include "Datas/CharacterDatas.h"
#include "Monster/MonsterAnimInstance.h"
#include "Monster/Monster_Enums.h"
#include "Animation/AnimMontage.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"





// Sets default values
ACharacter_Base::ACharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));

	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}




// Called when the game starts or when spawned
void ACharacter_Base::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* Inst = GetWorld()->GetGameInstance<UMyGameInstance>();


	if (nullptr != Inst)
	{
		CharacterData = Inst->GetCharacterData(DataName);
	}

	SetAllAnimation(CharacterData->AllAnimations);

	HP = CharacterData->HP;

	 // //기존에 있던 적들의 타겟클래스의 배열에 나를 넣는다
	 // for (FString TargetTag : CharacterData->TagetTags)
	 // {
	 // 
	 // 	TArray<AActor*> TargetActors;
	 // 	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);
	 // 
	 // 	for (AActor* TargetActor : TargetActors)
	 // 	{
	 // 		ACharacter_Base* Target = Cast<ACharacter_Base>(TargetActor);
	 // 		Target->TargetActorArrayClass.TargetActorArray.Add(this);
	 // 	}
	 // 
	 // }
	 // 
	 // //기존에 있던 적들을 내 타겟클래스의 배열안에 넣는다
	 // for (FString TargetTag : CharacterData->TagetTags)
	 // {
	 // 
	 // 	TArray<AActor*> TargetActors;
	 // 	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);
	 // 
	 // 	for (AActor* TargetActor : TargetActors)
	 // 	{
	 // 		TargetActorArrayClass.TargetActorArray.Add(TargetActor);
	 // 	}
	 // 
	 // }


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

UBlackboardComponent* ACharacter_Base::GetBlackboardComponent()
{
	if (nullptr == BlackboardComponent)
	{
		AAIController* AiCon = GetController<AAIController>();

		if (nullptr == AiCon)
		{
			return nullptr;
		}

		BlackboardComponent = AiCon->GetBlackboardComponent();
	}

	return BlackboardComponent;
}

