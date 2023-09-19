// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Datas/TargetActorArrayClass.h"
#include "Character_Base.generated.h"



UCLASS()
class JSPORTPOLIO_API ACharacter_Base : public APawn
{

public:
	GENERATED_BODY()

	// Sets default values for this character's properties
	ACharacter_Base();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAcdasdasdcess = "true"))
	FName DataName = "NONE";

	int AniState = 0;

	int GetAniState()
	{
		return AniState;
	}

	template<typename EnumType>
	void SetAniState(EnumType State)
	{
		AniState = static_cast<int>(State);
	}

	template<typename EnumType>
	void SetAllAnimation(const TMap<EnumType, class UAnimMontage*>& _MapAnimation)
	{
		for (TPair<EnumType, UAnimMontage*> Pair : _MapAnimation)
		{
			AllAnimations.Add(static_cast<int>(Pair.Key), Pair.Value);
		}
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Scene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCharacterMovementComponent* PawnMoveCom;

	struct FCharacterDatas* CharacterData;

	int HP;

	TMap<int, class UAnimMontage*> AllAnimations;

	FORCEINLINE class UBehaviorTree* GetBehaviorTree();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UBlackboardComponent* BlackboardComponent;

	class UBlackboardComponent* GetBlackboardComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTargetActorArrayClass* TargetActorArrayClass;

	TArray<AActor*> TargetArray;

	// UTargetActorArrayClass Targets;
	// UTargetActorArrayClass TargetActorArrayClass;

};
