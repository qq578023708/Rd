// Fill out your copyright notice in the Description page of Project Settings.


#include "RdGameFeaturesPolicies.h"

URdGameFeaturesPolicies& URdGameFeaturesPolicies::Get()
{
	return UGameFeaturesSubsystem::Get().GetPolicy<URdGameFeaturesPolicies>();
}

URdGameFeaturesPolicies::URdGameFeaturesPolicies(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}
