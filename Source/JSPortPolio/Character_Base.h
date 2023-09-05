// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character_Base.generated.h"


UCLASS()
class JSPORTPOLIO_API ACharacter_Base : public ACharacter
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

	int Anistate = 0;

	int GetAnistate()
	{
		return Anistate;
	}

	template<typename EnumType>
	void SetAniState(EnumType _AniState)
	{
		AniState = static_cast<int>(_AniState);
	}

	struct FCharacterDatas* CharacterData;

	TMap<int, class UAnimMontage*> AllAnimations;

	FORCEINLINE class UBehaviorTree* GetBehaviorTree();
	

};
