// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LLCConfig.generated.h"

USTRUCT(BlueprintType)
struct FBuildInfo {

	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Buildinfo")
		FString Version;
};

/**
 * 
 */
UCLASS()
class LOWLIGHTCOMBAT_API ULLCConfig : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "LLCConfig")
		static FBuildInfo GetBuildInfo();
};

