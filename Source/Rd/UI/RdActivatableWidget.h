// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "RdActivatableWidget.generated.h"

/**
 * 
 */
struct FUIInputConfig;

UENUM(BlueprintType)
enum class ERdWidgetInputMode:uint8
{
	Default,
	GameAndMenu,
	Game,
	Menu
};

UCLASS(Abstract,Blueprintable)
class RD_API URdActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
	URdActivatableWidget(const FObjectInitializer& ObjectInitializer);

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

#if WITH_EDITOR
	virtual void ValidateCompiledWidgetTree(const UWidgetTree& BlueprintWidgetTree, IWidgetCompilerLog& CompileLog) const override;
#endif

protected:
	UPROPERTY(EditDefaultsOnly,Category=Input)
	ERdWidgetInputMode InputConfig=ERdWidgetInputMode::Default;

	UPROPERTY(EditDefaultsOnly,Category=Input)
	EMouseCaptureMode GameMouseCapturemode=EMouseCaptureMode::CapturePermanently;
	
};
