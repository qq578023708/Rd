// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFeaturesProjectPolicies.h"
#include "RdGameFeaturesPolicies.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI,Config=Game)
class  URdGameFeaturesPolicies : public UDefaultGameFeaturesProjectPolicies
{
	GENERATED_BODY()
public:
	RD_API static URdGameFeaturesPolicies& Get();
	URdGameFeaturesPolicies(const FObjectInitializer& ObjectInitializer);
};
