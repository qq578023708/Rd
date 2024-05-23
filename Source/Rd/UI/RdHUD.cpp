// Copyright Bob, Inc. All Rights Reserved.


#include "RdHUD.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Components/GameFrameworkComponentManager.h"

ARdHUD::ARdHUD(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled=false;
}

void ARdHUD::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}

void ARdHUD::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this,UGameFrameworkComponentManager::NAME_GameActorReady);
	Super::BeginPlay();
}

void ARdHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);
	Super::EndPlay(EndPlayReason);
}

void ARdHUD::GetDebugActorList(TArray<AActor*>& InOutList)
{
	UWorld* World=GetWorld();
	Super::GetDebugActorList(InOutList);

	for (TObjectIterator<UAbilitySystemComponent> It;It;++It)
	{
		if(UAbilitySystemComponent* ASC=*It)
		{
			if(!ASC->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
			{
				AActor* AvatarActor=ASC->GetAvatarActor();
				AActor* OwnerActor=ASC->GetOwnerActor();

				if(AvatarActor && UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(AvatarActor))
				{
					AddActorToDebugList(AvatarActor,InOutList,World);
				}
				else if(OwnerActor && UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwnerActor))
				{
					AddActorToDebugList(OwnerActor,InOutList,World);
				}
			}
		}
	}
}
