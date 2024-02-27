// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DW_BasePickup.generated.h"

class UNiagaraComponent;
class UBoxComponent;

UCLASS()
class DRONEWARS_API ADW_BasePickup : public AActor
{
    GENERATED_BODY()

public:
    ADW_BasePickup();

protected:
    UPROPERTY(EditAnywhere)
    UNiagaraComponent* PickupNiagara;

    UPROPERTY(EditAnywhere)
    UBoxComponent* OverlapBox;
};
