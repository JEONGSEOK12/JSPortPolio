// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCallAnimSignature, Monster_Enum, Anim);




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
	
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	




	UPROPERTY(Category = "CharacterData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAcdasdasdcess = "true"))
	FName DataName = "NONE";

public:

	void TestFuc();

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FCallAnimSignature AnimationDelegate;


	struct FCharacterDatas* CharacterData;

	FORCEINLINE class UBehaviorTree* GetBehaviorTree();
	
	void AnimCaller(Monster_Enum);


	class UBTTaskNode_Base* TaskBase;


};
