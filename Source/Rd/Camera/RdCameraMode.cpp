// Copyright Bob, Inc. All Rights Reserved.


#include "RdCameraMode.h"

#include "RdCameraComponent.h"
#include "RdPlayerCameraManager.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Canvas.h"
#include "GameFramework/Character.h"
#include "Misc/LowLevelTestAdapter.h"


FRdCameraModeView::FRdCameraModeView()
:Location(ForceInit)
,Rotation(ForceInit)
,ControlRotation(ForceInit)
,FieldOfView(RD_CAMERA_DEFAULT_FOV)
{
}

void FRdCameraModeView::Blend(const FRdCameraModeView& Other, float OtherWeight)
{
	if(OtherWeight<=0.0f)
	{
		return;
	}
	else if(OtherWeight>=1.0f)
	{
		*this=Other;
		return;
	}

	Location==FMath::Lerp(Location,Other.Location,OtherWeight);

	const FRotator DeltaRotation=(Other.Rotation-Rotation).GetNormalized();
	Rotation=Rotation+(OtherWeight*DeltaRotation);

	const FRotator DeltaControlRotation=(Other.ControlRotation-ControlRotation).GetNormalized();
	ControlRotation=ControlRotation+(OtherWeight*DeltaControlRotation);

	FieldOfView=FMath::Lerp(FieldOfView,Other.FieldOfView,OtherWeight);
}

URdCameraMode::URdCameraMode()
{
	FieldOfView=RD_CAMERA_DEFAULT_FOV;
	ViewPitchMin=RD_CAMERA_DEFAULT_PITCH_MIN;
	ViewPitchMax=RD_CAMERA_DEFAULT_PITCH_MAX;

	BlendTime=0.5f;
	BlendFunction=ERdCameraModeBlendFunction::EaseOut;
	BlendExponent=4.0f;
	BlendAlpha=1.0f;
	BlendWeight=1.0f;
}

URdCameraComponent* URdCameraMode::GetRdCameraComponent() const
{
	return  CastChecked<URdCameraComponent>(GetOuter());
}

UWorld* URdCameraMode::GetWorld() const
{
	return HasAnyFlags(RF_ClassDefaultObject) ? nullptr:GetOuter()->GetWorld();
}

AActor* URdCameraMode::GetTargetActor() const
{
	const URdCameraComponent* RdCameraComponent=GetRdCameraComponent();
	return RdCameraComponent->GetTargetActor();
}

void URdCameraMode::UpdateCameraMode(float DeltaTime)
{
	UpdateView(DeltaTime);
	UpdateBlending(DeltaTime);
}

void URdCameraMode::SetBlendWeight(float Weight)
{
	BlendWeight=FMath::Clamp(Weight,0.0f,1.0f);
	const float InvExponent=(BlendExponent>0.0f) ? (1.0f/BlendExponent) :1.0f;
	switch (BlendFunction)
	{
	case ERdCameraModeBlendFunction::Linear:
		BlendAlpha=BlendWeight;
		break;
	case ERdCameraModeBlendFunction::EaseIn:
		BlendAlpha=FMath::InterpEaseIn(0.0f,1.0f,BlendWeight,InvExponent);
		break;
	case ERdCameraModeBlendFunction::EaseOut:
		BlendAlpha=FMath::InterpEaseOut(0.0f,1.0f,BlendWeight,InvExponent);
		break;
	case ERdCameraModeBlendFunction::EaseInOut:
		BlendAlpha=FMath::InterpEaseInOut(0.0f,1.0f,BlendWeight,InvExponent);
		break;
	default:
		checkf(false,TEXT("SetBlendWeight:Invalid BlendFunction [%d]\n"),(uint8)BlendFunction)
		break;
		
	}
}

void URdCameraMode::DrawDebug(UCanvas* Canvas) const
{
	check(Canvas);
	FDisplayDebugManager& DisplayDebugManager=Canvas->DisplayDebugManager;
	DisplayDebugManager.SetDrawColor(FColor::White);
	DisplayDebugManager.DrawString(FString::Printf(TEXT("   RdGameMode:%s (%f)"),*GetName(),BlendWeight));
}

FVector URdCameraMode::GetPivotLocation() const
{
	const AActor* TargetActor=GetTargetActor();
	check(TargetActor);
	if (const APawn* TargetPawn=Cast<APawn>(TargetActor))
	{
		if(const ACharacter* TargetCharacter=Cast<ACharacter>(TargetPawn))
		{
			const ACharacter* TargetCharacterCD0=TargetCharacter->GetClass()->GetDefaultObject<ACharacter>();
			check(TargetCharacterCD0);

			const UCapsuleComponent* CapsuleComp=TargetCharacter->GetCapsuleComponent();
			check(CapsuleComp);

			const UCapsuleComponent* CapsuleCompCD0=TargetCharacterCD0->GetCapsuleComponent();
			check(CapsuleCompCD0);

			const float DefaultHalfHeight=CapsuleCompCD0->GetUnscaledCapsuleHalfHeight();
			const float ActualHalfHeight=CapsuleComp->GetUnscaledCapsuleHalfHeight();
			const float HeightAdjustment=(DefaultHalfHeight-ActualHalfHeight)+TargetCharacterCD0->BaseEyeHeight;

			return TargetCharacter->GetActorLocation()+(FVector::UpVector*HeightAdjustment);
		}

		return TargetPawn->GetPawnViewLocation();
	}

	return TargetActor->GetActorLocation();
}

FRotator URdCameraMode::GetPivotRotation() const
{

	const AActor* TargetActor=GetTargetActor();
	check(TargetActor);

	if(const APawn* TargetPawn=Cast<APawn>(TargetActor))
	{
		return TargetPawn->GetViewRotation();
	}

	return TargetActor->GetActorRotation();
}

void URdCameraMode::UpdateView(float DeltaTime)
{
	FVector PivotLocation=GetPivotLocation();
	FRotator PivotRotation=GetPivotRotation();
	PivotRotation.Pitch=FMath::ClampAngle(PivotRotation.Pitch,ViewPitchMin,ViewPitchMax);
	View.Location=PivotLocation;
	View.Rotation=PivotRotation;
	View.ControlRotation=View.Rotation;
	View.FieldOfView=FieldOfView;
}

void URdCameraMode::UpdateBlending(float DeltaTime)
{
	if (BlendTime>0.0f)
	{
		BlendAlpha+=(DeltaTime/BlendTime);
		BlendAlpha=FMath::Min(BlendAlpha,1.0f);
	}
	else
	{
		BlendAlpha=1.0f;
	}

	const float Exponent=(BlendExponent>0.0f)?BlendExponent:1.0f;
	switch (BlendFunction)
	{
	case ERdCameraModeBlendFunction::Linear:
		BlendWeight=BlendAlpha;
		break;
	case ERdCameraModeBlendFunction::EaseIn:
		BlendWeight=FMath::InterpEaseIn(0.0f,1.0f,BlendAlpha,Exponent);
		break;
	case ERdCameraModeBlendFunction::EaseOut:
		BlendWeight=FMath::InterpEaseOut(0.0f,1.0f,BlendAlpha,Exponent);
		break;
	case ERdCameraModeBlendFunction::EaseInOut:
		BlendWeight=FMath::InterpEaseInOut(0.0f,1.0f,BlendAlpha,Exponent);
		break;
	default:
		checkf(false,TEXT("UpdateBlending:Invalid BlendFunction [%d]\n"),(uint8)BlendFunction);
		break;
	}
}

URdCameraModeStack::URdCameraModeStack()
{
	bIsActive=true;
}

void URdCameraModeStack::ActivateStack()
{
	if (!bIsActive)
	{
		bIsActive=true;
		for (URdCameraMode* CameraMode:CameraModeStack)
		{
			check(CameraMode);
			CameraMode->OnActivation();
		}
	}
}

void URdCameraModeStack::DeactivateStack()
{
	if (bIsActive)
	{
		bIsActive=false;
		for (URdCameraMode* CameraMode:CameraModeStack)
		{
			check(CameraMode);
			CameraMode->OnDeactivation();
		}
	}
}

void URdCameraModeStack::PushCameraMode(TSubclassOf<URdCameraMode> CameraModeClass)
{
	if(!CameraModeClass)
	{
		return;
	}
	URdCameraMode* CameraMode=GetCameraModeInstance(CameraModeClass);
	check(CameraMode);
	int32 StackSize=CameraModeStack.Num();
	if((StackSize>0) && (CameraModeStack[0]==CameraMode))
	{
		return;
	}
	int32 ExistingStackIndex=INDEX_NONE;
	float ExistingStackContribution=1.0f;
	for (int32 StackIndex=0;StackIndex<StackSize;++StackIndex)
	{
		if (CameraModeStack[StackIndex]==CameraMode)
		{
			ExistingStackIndex=StackIndex;
			ExistingStackContribution*=CameraMode->GetBlendWeight();
			break;
		}
		else
		{
			ExistingStackContribution*=(1.0f-CameraModeStack[StackIndex]->GetBlendWeight());
		}
	}
	if (ExistingStackIndex!=INDEX_NONE)
	{
		CameraModeStack.RemoveAt(ExistingStackIndex);
		StackSize--;
	}
	else
	{
		ExistingStackContribution=0.0f;
	}

	const bool bShouldBlend=((CameraMode->GetBlendTime()>0.0f) && (StackSize>0));
	const float BlendWeight=(bShouldBlend?ExistingStackContribution:1.0f);

	CameraMode->SetBlendWeight(BlendWeight);
	CameraModeStack.Insert(CameraMode,0);
	CameraModeStack.Last()->SetBlendWeight(1.0f);

	if(ExistingStackIndex==INDEX_NONE)
	{
		CameraMode->OnActivation();
	}
}

bool URdCameraModeStack::EvaluateStack(float DeltaTime, FRdCameraModeView& OutCameraModeView)
{
	if (!bIsActive)
	{
		return false;
	}

	UpdateStack(DeltaTime);
	BlendStack(OutCameraModeView);
	return true;
}

void URdCameraModeStack::DrawDebug(UCanvas* Canvas) const
{
	check(Canvas);
	FDisplayDebugManager& DisplayDebugManager=Canvas->DisplayDebugManager;

	DisplayDebugManager.SetDrawColor(FColor::Green);
	DisplayDebugManager.DrawString(FString(TEXT("  --- Camera Modes (Begin) ---")));
	for (const URdCameraMode* CameraMode:CameraModeStack)
	{
		check(CameraMode);
		CameraMode->DrawDebug(Canvas);
	}

	DisplayDebugManager.SetDrawColor(FColor::Green);
	DisplayDebugManager.DrawString(FString::Printf(TEXT(" --- Camera Modes (End) ---")));
}

void URdCameraModeStack::GetBlendInfo(float& OutWeightOfTopLayer, FGameplayTag& OutTagOfTopLayer) const
{
	if (CameraModeStack.Num()==0)
	{
		OutWeightOfTopLayer=1.0f;
		OutTagOfTopLayer=FGameplayTag();
		return;
	}
	else
	{
		URdCameraMode* TopEntry=CameraModeStack.Last();
		check(TopEntry);
		OutWeightOfTopLayer=TopEntry->GetBlendWeight();
		OutTagOfTopLayer=TopEntry->GetCameraTypeTag();
	}
}

URdCameraMode* URdCameraModeStack::GetCameraModeInstance(TSubclassOf<URdCameraMode> CameraModeClass)
{
	check(CameraModeClass);
	for (URdCameraMode* CameraMode:CameraModeInstances)
	{
		if (((CameraMode!=nullptr) && (CameraMode->GetClass()==CameraModeClass)))
		{
			return CameraMode;
		}
	}

	URdCameraMode* NewCameraMode=NewObject<URdCameraMode>(GetOuter(),CameraModeClass,NAME_None,RF_NoFlags);
	check(NewCameraMode);

	CameraModeInstances.Add(NewCameraMode);
	return  NewCameraMode;
}

void URdCameraModeStack::UpdateStack(float DeltaTime)
{
	const int32 StackSize=CameraModeStack.Num();
	if (StackSize<=0)
	{
		return;
	}

	int32 RemoveCount=0;
	int32 RemoveIndex=INDEX_NONE;

	for (int32 StackIndex=0;StackIndex<StackSize;++StackIndex)
	{
		URdCameraMode* CameraMode=CameraModeStack[StackIndex];
		check(CameraMode);

		CameraMode->UpdateCameraMode(DeltaTime);
		if (CameraMode->GetBlendWeight()>=1.0f)
		{
			RemoveIndex=(StackIndex+1);
			RemoveCount=(StackSize-RemoveIndex);
			break;
		}
	}

	if(RemoveCount>0)
	{
		for (int32 StackIndex=RemoveIndex;StackIndex<StackSize;++StackIndex)
		{
			URdCameraMode* CameraMode=CameraModeStack[StackIndex];
			check(CameraMode);
			CameraMode->OnDeactivation();
		}

		CameraModeStack.RemoveAt(RemoveIndex,RemoveCount);
	}
}

void URdCameraModeStack::BlendStack(FRdCameraModeView& OutCameraModeView) const
{
	const int32 StackSize=CameraModeStack.Num();
	if (StackSize<=0)
	{
		return;
	}

	const URdCameraMode* CameraMode=CameraModeStack[StackSize-1];
	check(CameraMode);

	OutCameraModeView=CameraMode->GetCameraModeView();
	for (int32 StackIndex=(StackSize-2);StackIndex>=0;--StackIndex)
	{
		CameraMode=CameraModeStack[StackIndex];
		check(CameraMode);

		OutCameraModeView.Blend(CameraMode->GetCameraModeView(),CameraMode->GetBlendWeight());
	}
}
