// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class JSPORTPOLIO_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();
	~UMyGameInstance();

	TSubclassOf<AActor> GetPlayerActor(FName _Name);

private:
	UPROPERTY()
	UDataTable* PlayerDatas;

	UPROPERTY()
	UDataTable* SubClassData;

	UPROPERTY()
	UDataTable* MeshDatas;

	UPROPERTY()
	UDataTable* MonsterDatas;



};
