// Fill out your copyright notice in the Description page of Project Settings.


#include "RdWorldSettings.h"

#include "EngineUtils.h"
#include "RdLogChannels.h"
#include "Engine/AssetManager.h"
#include "GameFramework/PlayerStart.h"
#include "Misc/UObjectToken.h"

ARdWorldSettings::ARdWorldSettings(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

#if WITH_EDITOR
void ARdWorldSettings::CheckForErrors()
{
	Super::CheckForErrors();
	FMessageLog MapCheck("MapCheck");
	for (TActorIterator<APlayerStart> PlayerStartIt(GetWorld());PlayerStartIt;++PlayerStartIt)
	{
		APlayerStart* PlayerStart=*PlayerStartIt;
		if(IsValid(PlayerStart) && PlayerStart->GetClass()==APlayerStart::StaticClass())
		{
			MapCheck.Warning()
			->AddToken(FUObjectToken::Create(PlayerStart))
			->AddToken(FTextToken::Create(FText::FromString("is a normal APlayerStart, replace with ARdPlayerStart.")));
		}
	}
}

#endif

//默认经验配置
FPrimaryAssetId ARdWorldSettings::GetDefaultGameplayExperience() const
{
	FPrimaryAssetId Result;
	if(!DefaultGameplayExperience.IsNull())
	{
		 Result = UAssetManager::Get().
			GetPrimaryAssetIdForPath(DefaultGameplayExperience.ToSoftObjectPath());
		if(!Result.IsValid())
		{
			UE_LOG(LogRdExperience,Error,TEXT("%s.DefaultGameplayExperience is %s but that failed to resolve an asset ID(you night need to add a path to the Asset Rules in your game feature plugin or project settings)"),
				*GetPathNameSafe(this),*DefaultGameplayExperience.ToString());
		}
	}
	return Result;
}
