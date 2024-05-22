// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "RdTaggedWidget.generated.h"

class UObject;
/**
 * 
 */
UCLASS(Abstract,Blueprintable)
class RD_API URdTaggedWidget : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	URdTaggedWidget(const FObjectInitializer& ObjectInitializer);

	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="HUD")
	FGameplayTagContainer HiddenByTags;

	UPROPERTY(EditAnywhere,Category="HUD")
	ESlateVisibility ShownVisibility=ESlateVisibility::Visible;

	UPROPERTY(EditAnywhere,Category="HUD")
	ESlateVisibility HiddenVisibility=ESlateVisibility::Collapsed;

	bool bWantsToBeVisible=true;
private:
	void OnWatchedTagsChanged();
};
