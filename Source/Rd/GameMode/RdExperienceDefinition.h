// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RdExperienceDefinition.generated.h"

class UGameFeatureAction;
class URdPawnData;
class URdExperienceActionSet;
/**
 * 
 */
UCLASS(BlueprintType,Const)
class URdExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	URdExperienceDefinition();

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

#if WITH_EDITORONLY_DATA
	virtual void UpdateAssetBundleData() override;
#endif

public:
	UPROPERTY(EditDefaultsOnly,Category=Gameplay)
	TArray<FString> GameFeaturesToEnable;

	UPROPERTY(EditDefaultsOnly,Category=Gameplay)
	TObjectPtr<const URdPawnData> DefaultPawnData;

	UPROPERTY(EditDefaultsOnly,Instanced,Category="Actions")
	TArray<TObjectPtr<UGameFeatureAction>> Actions;

	UPROPERTY(EditDefaultsOnly,Category=Gameplay)
	TArray<TObjectPtr<URdExperienceActionSet>> ActionSets;
	
};
