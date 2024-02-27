// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickups/DW_AmmoPickup.h"

void ADW_AmmoPickup::BeginPlay()
{
    Super::BeginPlay();

    Tags.Add("Ammo");
}
