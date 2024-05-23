﻿// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RdHUD.generated.h"

namespace EEndPlayReason
{
	enum Type:int;
}

class AActor;
class UObject;

/**
 * 
 */
UCLASS(Config=Game)
class RD_API ARdHUD : public AHUD
{
	GENERATED_BODY()
public:
	ARdHUD(const FObjectInitializer& ObjectInitializer=FObjectInitializer::Get());

protected:
	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void GetDebugActorList(TArray<AActor*>& InOutList) override;
};
