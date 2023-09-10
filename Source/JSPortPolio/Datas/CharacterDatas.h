// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include <Monster/Monster_Enums.h>
#include "UObject/NoExportTypes.h"
#include "CharacterDatas.generated.h"

/**
 * 
 */
USTRUCT()
struct JSPORTPOLIO_API FCharacterDatas : public FTableRowBase

{
	GENERATED_BODY()


	FCharacterDatas() {}
	~FCharacterDatas() {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TMap<Monster_Enum, class UAnimMontage*> AllAnimations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int MyValue2;



};


