// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DW_OverlayWidget.generated.h"

class ADW_BaseCharacter;
class ADW_PlayerController;
class USizeBox;
class UImage;
class ADW_PlayerCharacter;
class UTextBlock;
class UProgressBar;

UCLASS()
class DRONEWARS_API UDW_OverlayWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION()
    void UpdateTextAndProgressBar(float NewHealth);

    UFUNCTION()
    void UpdateCurrentAmmoText(int32 NewAmmo);

    void InitializeHealthBarPercentage();
    void InitializeCooldownBarPercentage();
    void InitializeHealthText();

    void SetHealthBarPercentage(float NewPercentage);
    void SetCurrentHealthText(const FText& NewText);
    void SetCurrentAmmoText(const FText& NewText);
    void SetEnemiesLeftText(const FText& NewText);
    void SetCrosshairLocation(const FVector& Vector);
    void BindDelegates();

    void UpdateShootProgressBar(float GetTimerRemaining);

    void TellPlayerThatEnemyHasSpawned();
    void TellPlayerThatEnemyHasDied();

    virtual void NativeConstruct() override;

protected:
    UPROPERTY(meta=(BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY(meta=(BindWidget))
    UProgressBar* ShootCooldown;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* CurrentHealth;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* MaxHealth;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* CurrentAmmo;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* EnemiesLeft;

    UPROPERTY(meta=(BindWidget))
    UImage* CrosshairImage;

    UPROPERTY(meta=(BindWidget))
    USizeBox* CrosshairSizeBox;

    UPROPERTY()
    ADW_BaseCharacter* PlayerChar;

    UPROPERTY()
    ADW_PlayerController* PC;

    FVector2D TargetLocation;

    int32 EnemyCount = 0;
};
