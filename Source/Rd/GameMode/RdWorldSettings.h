// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RdExperienceDefinition.h"
#include "GameFramework/WorldSettings.h"
#include "RdWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class RD_API ARdWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
public:
	ARdWorldSettings(const FObjectInitializer& ObjectInitializer);
#if WITH_EDITOR
	virtual void CheckForErrors() override;
#endif

public:
	FPrimaryAssetId GetDefaultGameplayExperience() const;

protected:
	UPROPERTY(EditDefaultsOnly,Category=GameMode)
	TSoftClassPtr<URdExperienceDefinition> DefaultGameplayExperience;

public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly,Category=PIE)
	bool ForceStandaloneNetMode=false;
#endif
	
	
};
