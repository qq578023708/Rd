// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RdExperienceActionSet.generated.h"

class UGameFeatureAction;

/**
 * 
 */
UCLASS(BlueprintType,NotBlueprintable)
class RD_API URdExperienceActionSet : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	URdExperienceActionSet();

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

#if WITH_EDITORONLY_DATA
	virtual void UpdateAssetBundleData() override;
#endif
public:
	UPROPERTY(EditAnywhere,Instanced,Category="Actions to Perform")
	TArray<TObjectPtr<UGameFeatureAction>> Actions;

	UPROPERTY(EditAnywhere,Category="Feature Dependencies")
	TArray<FString> GameFeaturesToEnable;
	
};
