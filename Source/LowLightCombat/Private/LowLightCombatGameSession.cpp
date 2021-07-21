// Fill out your copyright notice in the Description page of Project Settings.


#include "LowLightCombatGameSession.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

#include "Misc/Guid.h"
#include "OnlineAsyncTaskManager.h"
#include "SocketSubsystem.h"
#include "Templates/SharedPointer.h"
#include "Runtime/Sockets/Public/IPAddress.h"
#include "Engine/World.h"
#include "Online.h"

void ALowLightCombatGameSession::RegisterServer()
{

	UWorld* World = GetWorld();
	IOnlineSessionPtr SessionInt = Online::GetSessionInterface();

	FString name;
	GConfig->GetString(TEXT("ServerSettings"), TEXT("Name"), name, GGameIni);

	UE_LOG(LogTemp, Warning, TEXT("RegisterServer(): %s"), *name);

	FOnlineSessionSettings Settings;
	Settings.NumPublicConnections = 16;
	Settings.bShouldAdvertise = true;
	Settings.bAllowJoinInProgress = true;
	Settings.bIsLANMatch = false;
	Settings.bUsesPresence = true;
	Settings.bAllowJoinViaPresence = true;
	Settings.bIsDedicated = true;
	Settings.Set("VERSION", TEXT("Version X"));
	Settings.Set("SERVERNAME", *name);
	Settings.Set("PASSWORDPROTECTED", TEXT("false"));
	Settings.Set("PLAYERCOUNT", 0);
	Settings.Set("MAXPLAYERS", Settings.NumPublicConnections);

	SessionInt->CreateSession(0, GameSessionName, Settings);
	return;
}
