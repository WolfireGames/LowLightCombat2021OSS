// Fill out your copyright notice in the Description page of Project Settings.


#include "LLCConfig.h"
#include "JsonObjectConverter.h"

FBuildInfo ULLCConfig::GetBuildInfo()
{
	FBuildInfo buildInfo;
	FString path = FPaths::Combine(FPaths::ProjectContentDir(), *FString("Data"), *FString("buildinfo.json"));

	//FJsonObjectConverter::UStructToJsonObjectString<FBuildInfo>(buildInfo, outJSON);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *outJSON);


	if (FPaths::FileExists(path) == false) {
		UE_LOG(LogTemp, Warning, TEXT("File is not valid"));
	}

	FString outJSON;
	if (FFileHelper::LoadFileToString(outJSON, *path)) {
		FJsonObjectConverter::JsonObjectStringToUStruct<FBuildInfo>(outJSON, &buildInfo, 0, 0);
	}

	// Add Project version from engine configuration
	FString version;
	GConfig->GetString(TEXT("/Script/EngineSettings.GeneralProjectSettings"), TEXT("ProjectVersion"), version, GGameIni);
	buildInfo.Version = version;

	return buildInfo;
}
