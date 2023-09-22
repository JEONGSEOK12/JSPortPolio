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

	TargetActorArrayClass = CreateDefaultSubobject<UTargetActorArrayClass>(TEXT("TargetActorArray"));

	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);




	
}




// Called when the game starts or when spawned
void ACharacter_Base::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* Inst = GetWorld()->GetGameInstance<UMyGameInstance>();

	if (nullptr == CharacterData)
	{
		return;
	}



	if (nullptr != Inst)
	{
		CharacterData = Inst->GetCharacterData(DataName);
	}

	SetAllAnimation(CharacterData->AllAnimations);
	
	HP = CharacterData->HP;
	 //기존에 있던 적들의 타겟클래스의 배열에 나를 넣는다
	 for (FString TargetTag : CharacterData->TagetTags)
	 {
	 
	 	TArray<AActor*> TargetActors;
	 	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);

		if(TargetActors.Num()!=0)
		{

			for (AActor* TargetActor : TargetActors)
			{
				ACharacter_Base* Target = Cast<ACharacter_Base>(TargetActor);
				if(Target!=nullptr)
				{
					Target->TargetArray.Add(this);
				}
			}

		}
	 }
	 
	 //기존에 있던 적들을 내 타겟클래스의 배열안에 넣는다
	 for (FString TargetTag : CharacterData->TagetTags)
	 {
	 
	 	TArray<AActor*> TargetActors;
	 	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);

		if (TargetActors.Num() != 0)
		{

			for (AActor* TargetActor : TargetActors)
			{
				if (TargetActor != nullptr)
				{
					TargetArray.Add(TargetActor);
				}
			}

		}
	 }


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



void ACharacter_Base::MoveCharacter(FVector Dir,float Speed)
{
	Dir.Normalize();
	FVector MyDir = Dir;
	MyDir.Z = 0;

	FVector MyFoward = GetActorForwardVector();
	MyFoward.Normalize();
	MyFoward.Z = 0;

	FVector Cross = FVector::CrossProduct(MyDir, MyFoward);
	Cross.Normalize();

	float DirYaw = Dir.Rotation().Yaw;
	float MyYaw = MyFoward.Rotation().Yaw;
	float YawDiff = DirYaw - MyYaw;
	float DeltaSec = GetWorld()->GetDeltaSeconds();

	if (abs(YawDiff) >= 180)
	{
		YawDiff -= 360;
	}

	if (abs(YawDiff)>=3)
	{
		if (YawDiff >= 0)
		{
			MyYaw += DeltaSec * 50.f;
		}
		else
		{
			MyYaw -= DeltaSec * 50.f;
		}

		SetActorRotation(FRotator(0, MyYaw, 0));

	}
	if (abs(YawDiff) <= 10)
	{
		SetActorLocation(GetActorLocation() + Dir * Speed * DeltaSec);
	}
	
}
