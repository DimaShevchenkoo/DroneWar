// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawners/DW_PickupSpawner.h"
#include "Pickups/DW_BasePickup.h"

ADW_PickupSpawner::ADW_PickupSpawner()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADW_PickupSpawner::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle SpawnTimer;
    GetWorldTimerManager().SetTimer(SpawnTimer, this, &ThisClass::RespawnPickupAfterBeingPicked, RespawnTimer, true, 1.f);
}

void ADW_PickupSpawner::RespawnPickupAfterBeingPicked()
{
    if (!GetWorld() || !PickupClass) return;
    if (!bSpawned)
    {
        SpawnedActor = GetWorld()->SpawnActor<ADW_BasePickup>(PickupClass, GetActorLocation(), GetActorRotation());
        bSpawned = true;
    }
    if (SpawnedActor->IsActorBeingDestroyed())
    {
        bSpawned = false;
    }
}
