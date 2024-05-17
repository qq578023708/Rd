﻿#include "RdLogChannels.h"

DEFINE_LOG_CATEGORY(LogRd)
DEFINE_LOG_CATEGORY(LogRdExperience)
DEFINE_LOG_CATEGORY(LogRdAbilitySystem)
DEFINE_LOG_CATEGORY(LogRdTeams)

FString GetClientServerContextString(UObject* ContextObject)
{
	ENetRole Role=ROLE_None;
	if(AActor* Actor=Cast<AActor>(ContextObject))
	{
		Role=Actor->GetLocalRole();
	}
	else if(UActorComponent* Component=Cast<UActorComponent>(ContextObject))
	{
		Role=Component->GetOwnerRole();
	}

	if(Role!=ROLE_None)
	{
		return (Role==ROLE_Authority)?TEXT("Server") :TEXT("Client");
	}
	else
	{
#if WITH_EDITOR
		if(GIsEditor)
		{
			extern ENGINE_API FString GPlayInEditorContextString;
			return GPlayInEditorContextString;
		}
#endif
		
	}
	return TEXT("[Unknow]");
}
