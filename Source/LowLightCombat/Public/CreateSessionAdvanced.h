// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CreateSessionAdvanced.generated.h"

/**
 * 
 */
UCLASS()
class LOWLIGHTCOMBAT_API UCreateSessionAdvanced : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCosmetic, Category = "Session")
		static void CreateSessionAdvanced();
};
