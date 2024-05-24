// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "RdHeroComponent.generated.h"


UCLASS(Blueprintable,meta=(BlueprintSpawnableComponent))
class RD_API URdHeroComponent : public UPawnComponent,public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URdHeroComponent(const FObjectInitializer& ObjectInitializer);
};
