// Copyright Bob, Inc. All Rights Reserved.


#include "RdActivatableWidget.h"
#include "Editor/WidgetCompilerLog.h"

#define LOCTEXT_NAMESPACE "Rd"

URdActivatableWidget::URdActivatableWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

TOptional<FUIInputConfig> URdActivatableWidget::GetDesiredInputConfig() const
{
	switch (InputConfig)
	{
	case ERdWidgetInputMode::GameAndMenu:
		return FUIInputConfig(ECommonInputMode::All,GameMouseCapturemode);
	case ERdWidgetInputMode::Game:
		return FUIInputConfig(ECommonInputMode::Game,GameMouseCapturemode);
	case ERdWidgetInputMode::Menu:
		return FUIInputConfig(ECommonInputMode::Menu,GameMouseCapturemode);
	case ERdWidgetInputMode::Default:
	default:
		return TOptional<FUIInputConfig>();
	}
}

#if WITH_EDITOR
void URdActivatableWidget::ValidateCompiledWidgetTree(const UWidgetTree& BlueprintWidgetTree,
	IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledWidgetTree(BlueprintWidgetTree, CompileLog);
	if (!GetClass()->IsFunctionImplementedInScript(GET_FUNCTION_NAME_CHECKED(URdActivatableWidget, BP_GetDesiredFocusTarget)))
	{
		if (GetParentNativeClass(GetClass()) == URdActivatableWidget::StaticClass())
		{
			CompileLog.Warning(LOCTEXT("ValidateGetDesiredFocusTarget_Warning", "GetDesiredFocusTarget wasn't implemented, you're going to have trouble using gamepads on this screen."));
		}
		else
		{
			//TODO - Note for now, because we can't guarantee it isn't implemented in a native subclass of this one.
			CompileLog.Note(LOCTEXT("ValidateGetDesiredFocusTarget_Note", "GetDesiredFocusTarget wasn't implemented, you're going to have trouble using gamepads on this screen.  If it was implemented in the native base class you can ignore this message."));
		}
	}
}
#endif


#undef LOCTEXT_NAMESPACE