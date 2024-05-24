// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "RdCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class RD_API URdCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
public:
	virtual AActor* GetTargetActor() const{return  GetOwner();}
};
