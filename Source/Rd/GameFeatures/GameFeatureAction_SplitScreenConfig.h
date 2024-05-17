// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction_WorldActionBase.h"
#include "GameFeatureAction_SplitScreenConfig.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI,meta=(DisplayName="SplitScreen Config"))
class UGameFeatureAction_SplitScreenConfig final : public UGameFeatureAction_WorldActionBase
{
	GENERATED_BODY()
public:
	virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;

	virtual void AddToWorld(const FWorldContext& WorldContext, const FGameFeatureStateChangeContext& ChangeContext) override;

public:
	UPROPERTY(EditAnywhere,Category=Action)
	bool bDisableSplitScreen=true;

private:
	TArray<FObjectKey> LocalDisableVotes;
	static TMap<FObjectKey,int32> GlobalDisableVotes;
};
