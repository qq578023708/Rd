// Copyright Bob, Inc. All Rights Reserved.


#include "RdWeaponUserInterface.h"

#include "Equipment/RdEquipmentManagerComponent.h"

URdWeaponUserInterface::URdWeaponUserInterface(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void URdWeaponUserInterface::NativeConstruct()
{
	Super::NativeConstruct();
}

void URdWeaponUserInterface::NativeDestruct()
{
	Super::NativeDestruct();
}

void URdWeaponUserInterface::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (APawn* Pawn=GetOwningPlayerPawn())
	{
		if (URdEquipmentManagerComponent* EquipmentManager=Pawn->FindComponentByClass<URdEquipmentManagerComponent>())
		{
			if(URdWeaponInstance* NewInstance=EquipmentManager->GetFirstInstanceOfType<URdWeaponInstance>())
			{
				if(NewInstance!=CurrentInstance && NewInstance->GetInstigator()!=nullptr)
				{
					URdWeaponInstance* OldWeapon=CurrentInstance;
					CurrentInstance=NewInstance;
					RebuildWidgetFromWeapon();
					OnWeaponChanged(OldWeapon,CurrentInstance);
				}
			}
		}
	}
}

void URdWeaponUserInterface::RebuildWidgetFromWeapon()
{
}
