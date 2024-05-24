// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/RdEquipmentInstance.h"
#include "RdWeaponInstance.generated.h"

/**
 * 
 */
UCLASS()
class URdWeaponInstance : public URdEquipmentInstance
{
	GENERATED_BODY()
protected:
	UFUNCTION()
	void OnDeathStarted(AActor* OwningActor);
};
