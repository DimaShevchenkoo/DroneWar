// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickups/DW_BasePickup.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"

ADW_BasePickup::ADW_BasePickup()
{
    PrimaryActorTick.bCanEverTick = true;

    OverlapBox = CreateDefaultSubobject<UBoxComponent>("Overlap Box");
    RootComponent = OverlapBox;

    PickupNiagara = CreateDefaultSubobject<UNiagaraComponent>("Niagara Mesh");
    PickupNiagara->SetupAttachment(GetRootComponent());
}
