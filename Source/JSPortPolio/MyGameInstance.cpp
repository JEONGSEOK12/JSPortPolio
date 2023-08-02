// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "MyObject.h"



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