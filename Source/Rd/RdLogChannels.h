#pragma once

#include "Logging/LogMacros.h"

class UObject;

RD_API DECLARE_LOG_CATEGORY_EXTERN(LogRd,Log,All);
RD_API DECLARE_LOG_CATEGORY_EXTERN(LogRdExperience,Log,All);
RD_API DECLARE_LOG_CATEGORY_EXTERN(LogRdAbilitySystem,Log,All);
RD_API DECLARE_LOG_CATEGORY_EXTERN(LogRdTeams,Log,All);
RD_API FString GetClientServerContextString(UObject* ContextObject=nullptr);