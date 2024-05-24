// Copyright Bob, Inc. All Rights Reserved.


#include "RdEquipmentManagerComponent.h"
#include "RdEquipmentDefinition.h"
#include "RdEquipmentInstance.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RdEquipmentManagerComponent)
class FLifetimeProperty;
struct FReplicationFlags;

FString FRdAppliedEquipmentEntry::GetDebugString() const
{
	return FString::Printf(TEXT("%s of %s"),*GetNameSafe(Instance),*GetNameSafe(EquipmentDefinition.Get()));
}

void FRdEquipmentList::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	
}

void FRdEquipmentList::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
}

void FRdEquipmentList::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
}

URdEquipmentInstance* FRdEquipmentList::AddEntry(TSubclassOf<URdEquipmentDefinition> EquipmentDefinition)
{
	return nullptr;
}

void FRdEquipmentList::RemoveEntry(URdEquipmentInstance* Instance)
{
}

URdAbilitySystemComponent* FRdEquipmentList::GetAbilitySystemComponent() const
{
	return nullptr;
}

URdEquipmentManagerComponent::URdEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

URdEquipmentInstance* URdEquipmentManagerComponent::GetFirstInstanceOfType(
	TSubclassOf<URdEquipmentInstance> InstanceType)
{
	for (FRdAppliedEquipmentEntry& Entry:EquipmentList.Entries)
	{
		if(URdEquipmentInstance* Instance=Entry.Instance)
		{
			if(Instance->IsA(InstanceType))
			{
				return Instance;
			}
		}
	}
	return nullptr;
}

void URdEquipmentManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass,EquipmentList);
}


