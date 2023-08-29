// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "MyObject.h"
#include <Datas/CharacterDatas.h>


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



	FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/ChracterDatas.ChracterDatas'");
	ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

	if (DataTable.Succeeded())
	{
		CharacterDatas = DataTable.Object;
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


FCharacterDatas* UMyGameInstance::GetCharacterData(FName _Name)
{
	if (nullptr == CharacterDatas)
	{
		return nullptr;
	}

	FCharacterDatas* FindTable = CharacterDatas->FindRow<FCharacterDatas>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable;
}