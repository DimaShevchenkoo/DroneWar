// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/DW_BaseCharacter.h"
#include "DW_EnemyCharacter.generated.h"

class UWidgetComponent;
class ADW_PlayerCharacter;
class UAIPerceptionStimuliSourceComponent;
class UBehaviorTree;

UCLASS()
class DRONEWARS_API ADW_EnemyCharacter : public ADW_BaseCharacter
{
    GENERATED_BODY()

public:
    ADW_EnemyCharacter();
    void BindHealthToTheWidget();

    virtual void BeginPlay() override;
    virtual void Shoot() override;
    virtual void Destroyed() override;

    void RotateTowerToPlayer();
    void RotateBarrelToPlayer();

    bool CheckIfPlayerInFireRange();
    bool CheckIfBarrelInAngleRange(float CurrentAngle);
    bool CheckIfNothingIsBlockingVisibility();

    void TellGMAndPlayerThatEnemyHasSpawned();

protected:
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* TowerMesh;

    UPROPERTY()
    ADW_PlayerCharacter* PlayerChar;

    UPROPERTY(EditAnywhere)
    UWidgetComponent* HealthBar;

    UPROPERTY(EditAnywhere)
    float FireRange = 2000.f;

    UPROPERTY(EditAnywhere)
    float TowerRotationSpeed = 2.f;
};
