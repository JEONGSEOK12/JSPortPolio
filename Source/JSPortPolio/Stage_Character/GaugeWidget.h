// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Test_Player.h"
#include "GaugeWidget.generated.h"



/**
 * 
 */
UCLASS()
class JSPORTPOLIO_API UGaugeWidget : public UUserWidget
{
	GENERATED_BODY()



	ATest_Player* Player;
	
};
