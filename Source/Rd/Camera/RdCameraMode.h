// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "RdCameraMode.generated.h"

class AActor;
class UCanvas;
class URdCameraComponent;

UENUM(BlueprintType)
enum class ERdCameraModeBlendFunction:uint8
{
	Linear,
	EaseIn,
	EaseOut,
	EaseInOut,
	COUNT UMETA(Hidden)
};

struct FRdCameraModeView
{
public:
	FRdCameraModeView();
	void Blend(const FRdCameraModeView& Other,float OtherWeight);
public:
	FVector Location;
	FRotator Rotation;
	FRotator ControlRotation;
	float FieldOfView;
};

/**
 * 
 */
UCLASS(Abstract,NotBlueprintable)
class RD_API URdCameraMode : public UObject
{
	GENERATED_BODY()
public:
	URdCameraMode();
	URdCameraComponent* GetRdCameraComponent() const;
	virtual UWorld* GetWorld() const override;
	AActor* GetTargetActor() const;
	const FRdCameraModeView& GetCameraModeView() const{return View;}
	virtual void OnActivation(){}
	virtual void OnDeactivation(){}
	void UpdateCameraMode(float DeltaTime);
	float GetBlendTime() const{return BlendTime;}
	float GetBlendWeight() const{return BlendWeight;}
	void SetBlendWeight(float Weight);

	FGameplayTag GetCameraTypeTag() const
	{
		return CameraTag;
	}
	virtual void DrawDebug(UCanvas* Canvas) const;
protected:
	virtual FVector GetPivotLocation() const;
	virtual FRotator GetPivotRotation() const;

	virtual void UpdateView(float DeltaTime);
	virtual  void UpdateBlending(float DeltaTime);
protected:
	UPROPERTY(EditDefaultsOnly,Category="Blending")
	FGameplayTag CameraTag;
	
	FRdCameraModeView View;

	UPROPERTY(EditDefaultsOnly,Category="View",meta=(UIMin="5.0",UIMax="170",ClampMin="5.0",ClampMax="170"))
	float FieldOfView;

	UPROPERTY(EditDefaultsOnly,Category="View",meta=(UIMin="-89.9",UIMax="89.9",ClampMin="-89.9",ClampMax="89.9"))
	float ViewPitchMin;

	UPROPERTY(EditDefaultsOnly,Category="View",meta=(UIMin="-89.9",UIMax="89.9",ClampMin="-89.9",ClampMax="89.9"))
	float ViewPitchMax;

	UPROPERTY(EditDefaultsOnly,Category="Blending")
	float BlendTime;

	UPROPERTY(EditDefaultsOnly,Category="Blending")
	ERdCameraModeBlendFunction BlendFunction;

	UPROPERTY(EditDefaultsOnly,Category="Blending")
	float BlendExponent;

	float BlendAlpha;

	float BlendWeight;

protected:
	UPROPERTY(Transient)
	uint32 bResetInterpolation:1;
};

UCLASS()
class URdCameraModeStack : public UObject
{
	GENERATED_BODY()

public:
	URdCameraModeStack();
	void ActivateStack();
	void DeactivateStack();

	bool IsStackActivate() const {return bIsActive;}

	void PushCameraMode(TSubclassOf<URdCameraMode> CameraModeClass);

	bool EvaluateStack(float DeltaTime,FRdCameraModeView& OutCameraModeView);

	void DrawDebug(UCanvas* Canvas) const;

	void GetBlendInfo(float& OutWeightOfTopLayer,FGameplayTag& OutTagOfTopLayer) const;
protected:
	URdCameraMode* GetCameraModeInstance(TSubclassOf<URdCameraMode> CameraModeClass);

	void UpdateStack(float DeltaTime);
	void BlendStack(FRdCameraModeView& OutCameraModeView) const;

protected:
	bool bIsActive;

	UPROPERTY()
	TArray<TObjectPtr<URdCameraMode>> CameraModeInstances;

	UPROPERTY()
	TArray<TObjectPtr<URdCameraMode>> CameraModeStack;
};
