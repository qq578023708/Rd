// Copyright Bob, Inc. All Rights Reserved.


#include "RdEquipmentInstance.h"

void URdEquipmentInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void URdEquipmentInstance::OnRep_Instigator()
{
}
