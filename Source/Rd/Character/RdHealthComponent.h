// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"
#include "RdHealthComponent.generated.h"

class URdHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRdHealth_DeathEvent,AActor*,OwningActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FRdHealth_AttributeChanged,URdHealthComponent*,HealthComponent,float,OldValue,float,NewValue,AActor*,Instigator);

UENUM(BlueprintType)
enum class ERdDeathState:uint8
{
	NotDead=0,
	DeathStarted,
	DeathFinished
};
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RD_API URdHealthComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URdHealthComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable,BlueprintPure=false,Category="Health",meta=(ExpandBoolAsExecs="ReturnValue"))
	bool IsDeadOrDying() const{return (DeathState>ERdDeathState::NotDead);}

public:

	UPROPERTY(BlueprintAssignable)
	FRdHealth_DeathEvent OnDeathStarted;

	UPROPERTY(BlueprintAssignable)
	FRdHealth_DeathEvent OnDeathFinished;

protected:
	UFUNCTION()
	virtual void OnRep_DeathState(ERdDeathState OldDeathState);

protected:
	UPROPERTY(ReplicatedUsing=OnRep_DeathState)
	ERdDeathState DeathState;
};
