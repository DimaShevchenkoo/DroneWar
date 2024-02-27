// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DW_AITurretController.generated.h"

class ADW_EnemyCharacter;
class ADW_PlayerCharacter;

UCLASS()
class DRONEWARS_API ADW_AITurretController : public AAIController
{
    GENERATED_BODY()

public:
    bool CheckIfNothingIsBlockingVisibility();

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;

    bool InFireRange();
    void RotateTowerToPlayer();
    void RotateBarrelToPlayer();
    void Shoot();

protected:
    UPROPERTY()
    ADW_EnemyCharacter* EnemyChar;
};
