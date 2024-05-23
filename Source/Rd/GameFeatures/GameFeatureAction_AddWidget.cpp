﻿// Copyright Bob, Inc. All Rights Reserved.


#include "GameFeatureAction_AddWidget.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#include "GameFeaturesSubsystemSettings.h"
#include "Components/GameFrameworkComponentManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GameFeatureAction_AddWidget)
#define LOCTEXT_NAMESPACE "RdGameFeatures"

void UGameFeatureAction_AddWidget::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
{
	Super::OnGameFeatureDeactivating(Context);
	FPerContextData* ActiveData=ContextData.Find(Context);
	if(ensure(ActiveData))
	{
		Reset(*ActiveData);
	}
}

#if WITH_EDITORONLY_DATA

void UGameFeatureAction_AddWidget::AddAdditionalAssetBundleData(FAssetBundleData& AssetBundleData)
{
	for (const FRdHUDElementEntry& Entry:Widgets)
	{
		AssetBundleData.AddBundleAsset(UGameFeaturesSubsystemSettings::LoadStateClient,Entry.WidgetClass.ToSoftObjectPath().GetAssetPath());
	}
}
#endif

#if WITH_EDITOR
EDataValidationResult UGameFeatureAction_AddWidget::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result=CombineDataValidationResults(Super::IsDataValid(Context),EDataValidationResult::Valid);
	{
		int32 EntryIndex=0;
		for (const FRdHUDLayoutRequest& Entry:Layout)
		{
			if(Entry.LayoutClass.IsNull())
			{
				Result=EDataValidationResult::Invalid;
				Context.AddError(FText::Format(LOCTEXT("LayoutHasNullClass","Null WidgetClass at index {0} in Layout"),FText::AsNumber(EntryIndex)));
			}

			if (!Entry.LayerID.IsValid())
			{
				Result=EDataValidationResult::Invalid;
				Context.AddError(FText::Format(LOCTEXT("LayoutHasNoTag","LayerID is not set at index {0} in Widgets"),FText::AsNumber(EntryIndex)));
			}

			++EntryIndex;
		}
	}

	{
		int32 EntryIndex=0;
		for (const FRdHUDElementEntry& Entry:Widgets)
		{
			if(Entry.WidgetClass.IsNull())
			{
				Result=EDataValidationResult::Invalid;
				Context.AddError(FText::Format(LOCTEXT("EntryHasNullClass","Null WidgetClass at index {0} in Entry"),FText::AsNumber(EntryIndex)));
			}

			if (!Entry.SlotID.IsValid())
			{
				Result=EDataValidationResult::Invalid;
				Context.AddError(FText::Format(LOCTEXT("EntryHasNoTag","SlotID is not set at index {0} in Entry"),FText::AsNumber(EntryIndex)));
			}

			++EntryIndex;
		}
	}
	return Result;
}
#endif

void UGameFeatureAction_AddWidget::AddToWorld(const FWorldContext& WorldContext,
	const FGameFeatureStateChangeContext& ChangeContext)
{
	UWorld* World=WorldContext.World();
	UGameInstance* GameInstance=WorldContext.OwningGameInstance;
	FPerContextData& ActiveData=ContextData.FindOrAdd(ChangeContext);
	if ((GameInstance!=nullptr) && (World!=nullptr) && World->IsGameWorld())
	{
		if(UGameFrameworkComponentManager* ComponentManager=UGameInstance::GetSubsystem<UGameFrameworkComponentManager>(GameInstance))
		{
			//@TODO...
			//TSoftClassPtr<AActor> HUDActorClass
		}
	}
}

void UGameFeatureAction_AddWidget::Reset(FPerContextData& ActiveData)
{
}

void UGameFeatureAction_AddWidget::HandleActorExtension(AActor* Actor, FName EventName,
	FGameFeatureStateChangeContext ChangeContext)
{
}

void UGameFeatureAction_AddWidget::AddWidgets(AActor* Actor, FPerContextData& ActiveData)
{
}

void UGameFeatureAction_AddWidget::RemoveWidgets(AActor* Actor, FPerContextData& ActiveData)
{
}

#undef LOCTEXT_NAMESPACE