// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "AttributeSet.h"
#include "GameplayAbilitySpecHandle.h"
#include "RdAbilitySystemComponent.h"
#include "Engine/DataAsset.h"
#include "RdAbilitySet.generated.h"

USTRUCT()
struct FRdAbilitySet_GrantedHandles
{
	GENERATED_BODY()
public:
	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);
	void AddAttributeSet(UAttributeSet* Set);
	void TakeFromAbilitySystem(URdAbilitySystemComponent* RdASC);

protected:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;
};

/**
 * 
 */
UCLASS()
class RD_API URdAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()
};
