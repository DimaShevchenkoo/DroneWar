// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/DW_MainMenuWidget.h"

#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundClass.h"

void UDW_MainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    StartGameButton->OnClicked.AddDynamic(this, &ThisClass::StartGame);
    SettingsButton->OnClicked.AddDynamic(this, &ThisClass::ShowSettings);
    ExitGameButton->OnClicked.AddDynamic(this, &ThisClass::ExitGame);
    ReturnToMenuButton->OnClicked.AddDynamic(this, &ThisClass::ReturnToMenu);
    SoundSlider->OnValueChanged.AddDynamic(this, &ThisClass::ChangeGlobalVolume);
    ReturnToMenuButton->SetVisibility(ESlateVisibility::Hidden);
    SoundSlider->SetVisibility(ESlateVisibility::Hidden);
    ChangeVolumeText->SetVisibility(ESlateVisibility::Hidden);
}

void UDW_MainMenuWidget::StartGame()
{
    UGameplayStatics::OpenLevel(GetWorld(), "GameMap");
}

void UDW_MainMenuWidget::ShowSettings()
{
    ReturnToMenuButton->SetVisibility(ESlateVisibility::Visible);
    StartGameButton->SetVisibility(ESlateVisibility::Hidden);
    SettingsButton->SetVisibility(ESlateVisibility::Hidden);
    ExitGameButton->SetVisibility(ESlateVisibility::Hidden);
    SoundSlider->SetVisibility(ESlateVisibility::Visible);
    ChangeVolumeText->SetVisibility(ESlateVisibility::Visible);
}

void UDW_MainMenuWidget::ReturnToMenu()
{
    ReturnToMenuButton->SetVisibility(ESlateVisibility::Hidden);
    StartGameButton->SetVisibility(ESlateVisibility::Visible);
    SettingsButton->SetVisibility(ESlateVisibility::Visible);
    ExitGameButton->SetVisibility(ESlateVisibility::Visible);
    SoundSlider->SetVisibility(ESlateVisibility::Hidden);
    ChangeVolumeText->SetVisibility(ESlateVisibility::Hidden);
}

void UDW_MainMenuWidget::ChangeGlobalVolume(float NewValue)
{
    if (!SC_Main) return;
    NewValue = FMath::Clamp(NewValue, 0.f, 1.f);
    SC_Main->Properties.Volume = NewValue;
}

void UDW_MainMenuWidget::ExitGame()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}
