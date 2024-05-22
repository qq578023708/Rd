// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RdActivatableWidget.h"
#include "RdHUDLayout.generated.h"

class UCommonActivatableWidget;
class UObject;

/**
 * 
 */
UCLASS(Abstract,BlueprintType,Blueprintable,meta=(DisplayName="Rd HUD Layout"))
class RD_API URdHUDLayout : public URdActivatableWidget
{
	GENERATED_BODY()
public:
	URdHUDLayout(const FObjectInitializer& ObjectInitializer);
	virtual void NativeOnInitialized() override;
protected:
	void HandleEscapeAction();

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UCommonActivatableWidget> EscapeMenuClass;
};
