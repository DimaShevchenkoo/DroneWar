// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickups/DW_HealthPickup.h"

void ADW_HealthPickup::BeginPlay()
{
    Super::BeginPlay();

    Tags.Add("Health");
}
