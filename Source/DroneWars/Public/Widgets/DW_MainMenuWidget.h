// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DW_MainMenuWidget.generated.h"

class UTextBlock;
class USlider;
class UProgressBar;
class UButton;

UCLASS()
class DRONEWARS_API UDW_MainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

protected:
    UFUNCTION()
    void StartGame();

    UFUNCTION()
    void ShowSettings();

    UFUNCTION()
    void ExitGame();

    UFUNCTION()
    void ReturnToMenu();

    UFUNCTION()
    void ChangeGlobalVolume(float NewValue);

    UPROPERTY(meta=(BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta=(BindWidget))
    UButton* SettingsButton;

    UPROPERTY(meta=(BindWidget))
    UButton* ReturnToMenuButton;

    UPROPERTY(meta=(BindWidget))
    UButton* ExitGameButton;

    UPROPERTY(meta=(BindWidget))
    USlider* SoundSlider;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* ChangeVolumeText;

    UPROPERTY(EditAnywhere)
    USoundClass* SC_Main;
};
