// Copyright Bob, Inc. All Rights Reserved.


#include "GameFeatureAction_SplitScreenConfig.h"
#define LOCTEXT_NAMESPACE "RdGameFeatures"

TMap<FObjectKey,int32> UGameFeatureAction_SplitScreenConfig::GlobalDisableVotes;

void UGameFeatureAction_SplitScreenConfig::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
{
	Super::OnGameFeatureDeactivating(Context);
	for (int32 i=LocalDisableVotes.Num()-1;i>=0;i--)
	{
		FObjectKey ViewportKey=LocalDisableVotes[i];
		UGameViewportClient* GVP=Cast<UGameViewportClient>(ViewportKey.ResolveObjectPtr());
		const FWorldContext* WorldContext=GEngine->GetWorldContextFromGameViewport(GVP);
		if (GVP && WorldContext)
		{
			if(!Context.ShouldApplyToWorldContext(*WorldContext))
			{
				continue;
			}
		}

		int32& VoteCount=GlobalDisableVotes[ViewportKey];
		if(VoteCount<=1)
		{
			GlobalDisableVotes.Remove(ViewportKey);
			if(GVP && WorldContext)
			{
				GVP->SetForceDisableSplitscreen(false);
			}
		}
		else
		{
			--VoteCount;
		}
		LocalDisableVotes.RemoveAt(i);
	}
}

void UGameFeatureAction_SplitScreenConfig::AddToWorld(const FWorldContext& WorldContext,
	const FGameFeatureStateChangeContext& ChangeContext)
{
	if(bDisableSplitScreen)
	{
		if(UGameInstance* GameInstance=WorldContext.OwningGameInstance)
		{
			if(UGameViewportClient* VC=GameInstance->GetGameViewportClient())
			{
				FObjectKey ViewportKey(VC);
				LocalDisableVotes.Add(ViewportKey);
				int32& VoteCount=GlobalDisableVotes.FindOrAdd(ViewportKey);
				VoteCount++;
				if(VoteCount==1)
				{
					VC->SetForceDisableSplitscreen(true);
				}
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
