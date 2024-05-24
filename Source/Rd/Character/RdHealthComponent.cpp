// Copyright Bob, Inc. All Rights Reserved.


#include "RdHealthComponent.h"

URdHealthComponent::URdHealthComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	DeathState=ERdDeathState::NotDead;
}

void URdHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void URdHealthComponent::OnRep_DeathState(ERdDeathState OldDeathState)
{
}
