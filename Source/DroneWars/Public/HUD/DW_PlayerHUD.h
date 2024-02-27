// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DW_PlayerHUD.generated.h"

class UDW_PlayerLostWidget;
class UDW_PlayerWonWidget;
class ADW_PlayerController;
class UDW_OverlayWidget;

UCLASS()
class DRONEWARS_API ADW_PlayerHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    void ShowShootCooldown(float GetTimerRemaining);
    void SetCrosshairLocation(const FVector& Vector);

    void CreatePlayerWonWidget();
    void CreatePlayerLostWidget();

    void TellPlayerThatEnemyHasSpawned();
    void TellPlayerThatEnemyHasDied();

protected:
    UPROPERTY()
    ADW_PlayerController* PC;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> PlayerOverlayClass;

    UPROPERTY()
    UDW_OverlayWidget* PlayerOverlayWidget;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> PlayerWonClass;

    UPROPERTY()
    UDW_PlayerWonWidget* PlayerWonWidget;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> PlayerLostClass;

    UPROPERTY()
    UDW_PlayerLostWidget* PlayerLostWidget;
};
