// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Weapons/RdWeaponInstance.h"
#include "RdWeaponUserInterface.generated.h"

class URdWeaponInstance;
class UObject;
struct FGeometry;

/**
 * 
 */
UCLASS()
class RD_API URdWeaponUserInterface : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	URdWeaponUserInterface(const FObjectInitializer& ObjectInitializer=FObjectInitializer::Get());

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponChanged(URdWeaponInstance* OldWeapon,URdWeaponInstance* NewWeapon);

private:
	void RebuildWidgetFromWeapon();

private:
	UPROPERTY(Transient)
	TObjectPtr<URdWeaponInstance> CurrentInstance;
};
