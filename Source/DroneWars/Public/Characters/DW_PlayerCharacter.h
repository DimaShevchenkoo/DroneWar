// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/DW_BaseCharacter.h"
#include "DW_PlayerCharacter.generated.h"

class ADW_Crosshair;
class UFloatingPawnMovement;

UCLASS()
class DRONEWARS_API ADW_PlayerCharacter : public ADW_BaseCharacter
{
    GENERATED_BODY()

public:
    ADW_PlayerCharacter();

    virtual void Shoot() override;
    virtual void HandleShootCooldown() override;

    virtual void Tick(float DeltaSeconds) override;
    virtual void Destroyed() override;

    void CalculateCooldownProgressBar();
    void CalculateAndSetCrosshairLocation();

    FORCEINLINE UFloatingPawnMovement* GetPawnMovement() { return PawnMovement; }

protected:
    UPROPERTY(EditAnywhere)
    UFloatingPawnMovement* PawnMovement;
};
