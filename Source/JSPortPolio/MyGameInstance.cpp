// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

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