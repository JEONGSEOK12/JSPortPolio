// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

/**
 * 
 */
USTRUCT()
struct JSPORTPOLIO_API FMyObject : public FTableRowBase
{
	GENERATED_BODY()

		FMyObject() {}
	~FMyObject() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int MyValue;
};
