// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RdAnimationInstance.generated.h"

/**
 * 
 */
UCLASS(Config=Game)
class RD_API URdAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly)
	float GroundDistance=-1.0f;
};
