// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "LowLightCombatGameSession.generated.h"

/**
 * 
 */
UCLASS()
class LOWLIGHTCOMBAT_API ALowLightCombatGameSession : public AGameSession
{
	GENERATED_BODY()
		virtual void RegisterServer();

	
};
