// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RdEquipmentInstance.generated.h"

class AActor;
class APawn;
struct FFrame;


/**
 * 
 */
UCLASS()
class RD_API URdEquipmentInstance : public UObject
{
	GENERATED_BODY()
public:
	UObject* GetInstigator() const {return  Instigator;}

private:
	UFUNCTION()
	void OnRep_Instigator();
private:
	UPROPERTY(ReplicatedUsing=OnRep_Instigator)
	TObjectPtr<UObject> Instigator;

	UPROPERTY(Replicated)
	TArray<TObjectPtr<AActor>> SpawnedActors;
};
