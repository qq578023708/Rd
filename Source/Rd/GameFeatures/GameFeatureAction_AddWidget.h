// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActionWidget.h"
#include "CommonActivatableWidget.h"
#include "GameFeatureAction_WorldActionBase.h"
#include "GameplayTagContainer.h"
#include "UIExtensionSystem.h"
#include "GameFeatureAction_AddWidget.generated.h"

struct FWorldContext;
struct FComponentRequestHandle;

USTRUCT()
struct FRdHUDLayoutRequest
{
	GENERATED_BODY()
	TSoftClassPtr<UCommonActionWidget> LayoutClass;

	UPROPERTY(EditAnywhere,Category=UI,meta=(Categories="UI.Layer"))
	FGameplayTag LayerID;
	
};

USTRUCT()
struct FRdHUDElementEntry
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,Category=UI,meta=(AssetBundles="Client"))
	TSoftClassPtr<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere,Category=UI)
	FGameplayTag SlotID;
};

/**
 * 
 */
UCLASS(MinimalAPI,meta=(DisplayName="Add Widgets"))
class UGameFeatureAction_AddWidget : public UGameFeatureAction_WorldActionBase
{
	GENERATED_BODY()
public:
	virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;
#if WITH_EDITORONLY_DATA
	virtual void AddAdditionalAssetBundleData(FAssetBundleData& AssetBundleData) override;
#endif

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

private:
	UPROPERTY(EditAnywhere,Category=UI,meta=(TitleProperty="{LayerID} -> {LayoutClass}"))
	TArray<FRdHUDLayoutRequest> Layout;

	UPROPERTY(EditAnywhere,Category=UI,meta=(TitleProperty="{SlotID} -> {WidgetClass}"))
	TArray<FRdHUDElementEntry> Widgets;

private:
	struct FPerActorData
	{
		TArray<TWeakObjectPtr<UCommonActivatableWidget>> LayoutsAdded;
		TArray<FUIExtensionHandle> ExtensionHandles;
	};

	struct FPerContextData
	{
		TArray<TSharedPtr<FComponentRequestHandle>> ComponentRequests;
		TMap<FObjectKey,FPerActorData> ActorData;
	};

	TMap<FGameFeatureStateChangeContext,FPerContextData> ContextData;

	virtual void AddToWorld(const FWorldContext& WorldContext, const FGameFeatureStateChangeContext& ChangeContext) override;

	void Reset(FPerContextData& ActiveData);

	void HandleActorExtension(AActor* Actor,FName EventName,FGameFeatureStateChangeContext ChangeContext);

	void AddWidgets(AActor* Actor,FPerContextData& ActiveData);
	void RemoveWidgets(AActor* Actor,FPerContextData& ActiveData);
};
