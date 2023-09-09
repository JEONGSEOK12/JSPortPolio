// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"


UENUM(BlueprintType)
enum class Monster_Enum : uint8
{
	Default_Enum,
	Jump,
	Idle,
	Walk,
	Run,
	Scream,
	GetHit,
	Die

};

UENUM(BlueprintType)
enum class Monster_State : uint8
{
	Default_Enum,
	Walk,
	Run,
	Scream,
	GetHit,
	Die

};


