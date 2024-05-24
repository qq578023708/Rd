// Copyright Bob, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "RdPlayerCameraManager.generated.h"

class FDebugDisplayInfo;
class UCanvas;
class UObject;

#define RD_CAMERA_DEFAULT_FOV (80.0f)
#define RD_CAMERA_DEFAULT_PITCH_MIN (-89.0f)
#define RD_CAMERA_DEFAULT_PITCH_MAX (89.0f)

/**
 * 
 */
UCLASS()
class RD_API ARdPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
};
