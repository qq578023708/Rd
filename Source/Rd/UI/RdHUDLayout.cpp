// Copyright Bob, Inc. All Rights Reserved.


#include "RdHUDLayout.h"

#include "CommonUIExtensions.h"
#include "NativeGameplayTags.h"
#include "Input/CommonUIInputTypes.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MENU,"UI.Layer.Menu");
UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_ACTION_ESCAPE,"UI.Action.Escape");

URdHUDLayout::URdHUDLayout(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void URdHUDLayout::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	RegisterUIActionBinding(FBindUIActionArgs(FUIActionTag::ConvertChecked(TAG_UI_ACTION_ESCAPE),false,FSimpleDelegate::CreateUObject(this,&ThisClass::HandleEscapeAction)));
}

void URdHUDLayout::HandleEscapeAction()
{
	if(ensure(!EscapeMenuClass.IsNull()))
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(),TAG_UI_LAYER_MENU,EscapeMenuClass);
	}
}
