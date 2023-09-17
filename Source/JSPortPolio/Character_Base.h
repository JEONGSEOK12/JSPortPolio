// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Datas/TargetActorArrayDataAsset.h"
#include "Character_Base.generated.h"



UCLASS()
class JSPORTPOLIO_API ACharacter_Base : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
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

	struct FCharacterDatas* CharacterData;

	int HP;

	TMap<int, class UAnimMontage*> AllAnimations;

	FORCEINLINE class UBehaviorTree* GetBehaviorTree();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UBlackboardComponent* BlackboardComponent;

	class UBlackboardComponent* GetBlackboardComponent();

	UTargetActorArrayDataAsset TargetActorArray;

	// UTargetActorArrayClass Targets;
	// UTargetActorArrayClass TargetActorArrayClass;

};
