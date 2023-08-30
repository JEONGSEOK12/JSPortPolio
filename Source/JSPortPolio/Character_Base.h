// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include  <Datas/CharacterDatas.h>
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

	FORCEINLINE class UBehaviorTree* GetBehaviorTree()
	{
		return CharacterData->BehaviorTree;
	};





	UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName DataName = "NONE";

public:

	void TestFuc();

	class UBTTaskNode_Base* TaskBase;

	FCharacterDatas* CharacterData;

};
