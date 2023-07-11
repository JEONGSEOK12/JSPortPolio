// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	{
		FString DataPath = TEXT("/Script/Engine.Blueprint'/Game/Stage_Select_Map/BP_Cha.BP_Cha''");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			MyDatas = DataTable.Object;
		}
	}

}





UMyGameInstance::~UMyGameInstance()
{

}