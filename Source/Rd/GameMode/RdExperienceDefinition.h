// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction.h"
#include "RdExperienceActionSet.h"
#include "Character/RdPawnData.h"
#include "Engine/DataAsset.h"
#include "RdExperienceDefinition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Const)
class RD_API URdExperienceDefinition : public UPrimaryDataAsset
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
