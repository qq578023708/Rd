// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/RdAbilitySet.h"
#include "Components/PawnComponent.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "RdEquipmentManagerComponent.generated.h"

class UActorComponent;
class URdAbilitySystemComponent;
class URdEquipmentDefinition;
class URdEquipmentInstance;
class URdEquipmentManagerComponent;
class UObject;
struct FFrame;
struct FRdEquipmentList;
struct FNetDeltaSerializeInfo;
struct FReplicationFlags;


USTRUCT(BlueprintType)
struct FRdAppliedEquipmentEntry:public FFastArraySerializerItem
{
	GENERATED_BODY()
	FRdAppliedEquipmentEntry(){}
	FString GetDebugString() const;
private:
	friend FRdEquipmentList;
	friend URdEquipmentManagerComponent;

	UPROPERTY()
	TSubclassOf<URdEquipmentDefinition> EquipmentDefinition;

	UPROPERTY()
	TObjectPtr<URdEquipmentInstance> Instance=nullptr;

	UPROPERTY(NotReplicated)
	FRdAbilitySet_GrantedHandles GrantedHandles;
	
};

USTRUCT(BlueprintType)
struct FRdEquipmentList:public FFastArraySerializer
{
	GENERATED_BODY()
	FRdEquipmentList():OwnerComponent(nullptr){}

	FRdEquipmentList(UActorComponent* InOwnerComponent):OwnerComponent((InOwnerComponent)){}

public:
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices,int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices,int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices,int32 FinalSize);

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FRdAppliedEquipmentEntry,FRdEquipmentList>(Entries,DeltaParms,*this);
	}

	URdEquipmentInstance* AddEntry(TSubclassOf<URdEquipmentDefinition> EquipmentDefinition);
	void RemoveEntry(URdEquipmentInstance* Instance);
private:
	URdAbilitySystemComponent* GetAbilitySystemComponent() const;
	friend URdEquipmentManagerComponent;

private:
	UPROPERTY()
	TArray<FRdAppliedEquipmentEntry> Entries;

	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
	
};

template<>
struct TStructOpsTypeTraits<FRdEquipmentList> : public TStructOpsTypeTraitsBase2<FRdEquipmentList>
{
	enum {WithNetDeltaSerializer=true  };
};


UCLASS(BlueprintType,Const)
class URdEquipmentManagerComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URdEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable,BlueprintPure)
	URdEquipmentInstance* GetFirstInstanceOfType(TSubclassOf<URdEquipmentInstance> InstanceType);

	template <typename T>
	T* GetFirstInstanceOfType()
	{
		return (T*)GetFirstInstanceOfType(T::StaticClass());
	}

private:
	UPROPERTY(Replicated)
	FRdEquipmentList EquipmentList;
};

