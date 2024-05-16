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
			
		}
	}
	return Result;
}
