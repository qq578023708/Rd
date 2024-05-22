// Copyright Bob, Inc. All Rights Reserved.


#include "RdTaggedWidget.h"

URdTaggedWidget::URdTaggedWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void URdTaggedWidget::SetVisibility(ESlateVisibility InVisibility)
{
#if WITH_EDITORONLY_DATA
	if(IsDesignTime())
	{
		Super::SetVisibility(InVisibility);
		return;
	}
#endif
	bWantsToBeVisible=ConvertSerializedVisibilityToRuntime(InVisibility).IsVisible();
	if(bWantsToBeVisible)
	{
		ShownVisibility=InVisibility;
	}
	else
	{
		HiddenVisibility=InVisibility;
	}
	const bool bHasHiddenTags=false;

	const ESlateVisibility DesiredVisibility=(bWantsToBeVisible && !bHasHiddenTags) ? ShownVisibility:HiddenVisibility;
	if(GetVisibility()!=DesiredVisibility)
	{
		Super::SetVisibility(DesiredVisibility);
	}
	
}

void URdTaggedWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(!IsDesignTime())
	{
		SetVisibility(GetVisibility());
	}
}

void URdTaggedWidget::NativeDestruct()
{
	if(!IsDesignTime())
	{
		
	}
	Super::NativeDestruct();
}

void URdTaggedWidget::OnWatchedTagsChanged()
{
	const bool bHasHiddenTags=false;
	const ESlateVisibility DesiredVisibility=(bWantsToBeVisible && !bHasHiddenTags)?ShownVisibility:HiddenVisibility;
	if(GetVisibility()!=DesiredVisibility)
	{
		Super::SetVisibility(DesiredVisibility);
	}
}
