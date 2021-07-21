
#include "OnlineSubsystemPythonConfig.h"

UOnlineSubsystemPythonConfig::UOnlineSubsystemPythonConfig()
	: ServerAddress("master1.blackdrop.se:8081")
	, AuthorizationTicket("")
{

}

void UOnlineSubsystemPythonConfig::SetServerAddress(FString NewServerAddress)
{
	ServerAddress = NewServerAddress;
	SaveConfig();
}

void UOnlineSubsystemPythonConfig::SetAuthorizationTicket(FString NewAuthorizationTicket)
{
	AuthorizationTicket = NewAuthorizationTicket;
	SaveConfig();
}