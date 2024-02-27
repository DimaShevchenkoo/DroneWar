// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DW_PlayerController.generated.h"

class ADW_PlayerHUD;
struct FInputActionValue;
class ADW_PlayerCharacter;
class UInputAction;
class UInputMappingContext;

UCLASS()
class DRONEWARS_API ADW_PlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void SetupInputComponent() override;
    virtual void OnPossess(APawn* InPawn) override;
    virtual void BeginPlay() override;

    void ShowShootCooldown(float GetTimerRemaining);
    void SetCrosshairLocation(const FVector& Location);

    void CreatePlayerWonWidget();
    void CreatePlayerLostWidget();

    void TellPlayerThatEnemyHasSpawned();
    void TellPlayerThatEnemyHasDied();

protected:
    void Move(const FInputActionValue& Value);
    void MoveUpwards(const FInputActionValue& Value);
    void LookRight(const FInputActionValue& Value);
    void TurnBarrelUpwards(const FInputActionValue& Value);
    void Shoot(const FInputActionValue& Value);

    UPROPERTY(EditAnywhere)
    UInputMappingContext* InputMappingContext;

    UPROPERTY(EditAnywhere)
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere)
    UInputAction* MoveUpwardsAction;

    UPROPERTY(EditAnywhere)
    UInputAction* LookRightAction;

    UPROPERTY(EditAnywhere)
    UInputAction* ShootAction;

    UPROPERTY(EditAnywhere)
    UInputAction* TurnBarrelUpwardsAction;

    UPROPERTY(EditAnywhere)
    USoundBase* LostSound;

    UPROPERTY(EditAnywhere)
    USoundBase* WinSound;

private:
    UPROPERTY()
    ADW_PlayerCharacter* PlayerPawn;

    UPROPERTY()
    ADW_PlayerHUD* PlayerHUD;
};
