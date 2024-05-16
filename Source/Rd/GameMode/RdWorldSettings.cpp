// Fill out your copyright notice in the Description page of Project Settings.


#include "RdWorldSettings.h"

#include "Engine/AssetManager.h"

ARdWorldSettings::ARdWorldSettings(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void ARdWorldSettings::CheckForErrors()
{
	Super::CheckForErrors();
}

FPrimaryAssetId ARdWorldSettings::GetDefaultGameplayExperience() const
{
	FPrimaryAssetId Result;
	if(!DefaultGameplayExperience.IsNull())
	{
		 Result = UAssetManager::Get().
			GetPrimaryAssetIdForPath(DefaultGameplayExperience.ToSoftObjectPath());
		if(!Result.IsValid())
		{
			
		}
	}
	return Result;
}
