// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include <Monster/Monster_Enums.h>
#include "UObject/NoExportTypes.h"
#include "MonsterDatas.generated.h"

/**
 * 
 */
USTRUCT()
struct JSPORTPOLIO_API FMonsterDatas : public FTableRowBase

{
	GENERATED_BODY()


	FMonsterDatas() {}
	~FMonsterDatas() {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TMap<Monster_Enum, class UAnimMontage*> AllAnimations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int MyValue1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int MyValue2;



};


