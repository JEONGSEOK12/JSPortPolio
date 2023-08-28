// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "MyObject.h"
#include <Datas/MonsterDatas.h>


UMyGameInstance::UMyGameInstance()
{
	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/DT_MyData2.DT_MyData2'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			PlayerDatas = DataTable.Object;
		}
	}



	FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/MonsterDatas.MonsterDatas'");
	ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

	if (DataTable.Succeeded())
	{
		MonsterDatas = DataTable.Object;
	}





}





UMyGameInstance::~UMyGameInstance()
{

}


TSubclassOf<AActor> UMyGameInstance::GetPlayerActor(FName _Name)
{
	
	FMyObject* FindTable = PlayerDatas->FindRow<FMyObject>(_Name, _Name.ToString());
	TSubclassOf<AActor> Player = FindTable->Body;
		

		return Player;
}


FMonsterDatas* UMyGameInstance::GetMonsterData(FName _Name)
{
	if (nullptr == MonsterDatas)
	{
		return nullptr;
	}

	FMonsterDatas* FindTable = MonsterDatas->FindRow<FMonsterDatas>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable;
}