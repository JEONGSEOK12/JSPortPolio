// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "MyObject2.generated.h"

/**
 * 
 */
USTRUCT()
struct JSPORTPOLIO_API FMyObject2 : public FTableRowBase
{
	GENERATED_BODY()

		FMyObject2() {}
	~FMyObject2() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		AActor* Test1;
};
