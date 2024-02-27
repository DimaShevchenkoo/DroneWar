// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/DW_BasePickup.h"
#include "DW_HealthPickup.generated.h"

UCLASS()
class DRONEWARS_API ADW_HealthPickup : public ADW_BasePickup
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
