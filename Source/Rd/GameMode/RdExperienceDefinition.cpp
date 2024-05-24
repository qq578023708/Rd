// Copyright Bob, Inc. All Rights Reserved.


#include "RdExperienceDefinition.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#include "GameFeatureAction.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RdExperienceDefinition)

#define LOCTEXT_NAMESPACE "RdSystem"

URdExperienceDefinition::URdExperienceDefinition()
{
}

#if WITH_EDITOR

EDataValidationResult URdExperienceDefinition::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result=CombineDataValidationResults(Super::IsDataValid(Context),EDataValidationResult::Valid);
	int32 EntryIndex=0;
	for (const UGameFeatureAction* Action:Actions)
	{
		if (Action)
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
	if(!GetClass()->IsNative())
	{
		const UClass* ParentClass=GetClass()->GetSuperClass();
		const UClass* FirstNativeParent=ParentClass;
		while ((FirstNativeParent!=nullptr) && !FirstNativeParent->IsNative())
		{
			FirstNativeParent=FirstNativeParent->GetSuperClass();
		}

		if(FirstNativeParent!=ParentClass)
		{
			Context.AddError(FText::Format(LOCTEXT("ExperienceInheritenceIsUnsupported","Blueprint subclass of Blueprint experience is not currently supported(use composition via ActionSets instead).Parent class was {0} but should be {1}"),
				FText::AsCultureInvariant(GetPathNameSafe(ParentClass)),
				FText::AsCultureInvariant(GetPathNameSafe(FirstNativeParent))
				));
			Result=EDataValidationResult::Invalid;
		}
	}
	return Result;
}
#endif

#if WITH_EDITORONLY_DATA

void URdExperienceDefinition::UpdateAssetBundleData()
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
