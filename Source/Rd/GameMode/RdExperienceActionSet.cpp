// Copyright Bob, Inc. All Rights Reserved.


#include "RdExperienceActionSet.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#include "GameFeatureAction.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RdExperienceActionSet)
#define LOCTEXT_NAMESPACE "RdSystem"

URdExperienceActionSet::URdExperienceActionSet()
{
}
#if WITH_EDITOR
EDataValidationResult URdExperienceActionSet::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result=CombineDataValidationResults(Super::IsDataValid(Context),EDataValidationResult::Valid);
	int32 EntryIndex=0;
	for (const UGameFeatureAction* Action : Actions)
	{
		if(Action)
		{
			EDataValidationResult ChildResult=Action->IsDataValid(Context);
			Result=CombineDataValidationResults(Result,ChildResult);
		}
		else
		{
			Result=EDataValidationResult::Invalid;
			Context.AddError(FText::Format(LOCTEXT("ActionEntryIsNull","Null entry at index {0} in Actions"),FText::AsNumber(EntryIndex)));
		}

		++EntryIndex;
	}
	return Result;
}
#endif

#if WITH_EDITORONLY_DATA
void URdExperienceActionSet::UpdateAssetBundleData()
{
	Super::UpdateAssetBundleData();
	for (UGameFeatureAction* Action:Actions)
	{
		if (Action)
		{
			Action->AddAdditionalAssetBundleData(AssetBundleData);
		}
	}
}
#endif


#undef LOCTEXT_NAMESPACE