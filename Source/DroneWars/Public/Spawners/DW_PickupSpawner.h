// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DW_PickupSpawner.generated.h"

class ADW_BasePickup;

UCLASS()
class DRONEWARS_API ADW_PickupSpawner : public AActor
{
    GENERATED_BODY()

public:
    ADW_PickupSpawner();

protected:
    virtual void BeginPlay() override;

    void RespawnPickupAfterBeingPicked();

    UPROPERTY(EditAnywhere)
    TSubclassOf<ADW_BasePickup> PickupClass;

    UPROPERTY()
    ADW_BasePickup* SpawnedActor;

    UPROPERTY(EditAnywhere)
    float RespawnTimer = 5.f;

    bool bSpawned = false;
};
