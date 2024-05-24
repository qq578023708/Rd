// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RdPawnData.generated.h"

class APawn;
class URdAbilitySet;
class URdAbilityTagRelationshipMapping;
//TODO...


/**
 * 
 */
UCLASS(BlueprintType,Const,meta=(DisplayName="Pawn Data",ShortTooltip="Data asset used to define a pawn"))
class RD_API URdPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()
};
