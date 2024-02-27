// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/DW_OverlayWidget.h"
#include "ActorComponents/DW_HealthComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Characters/DW_PlayerCharacter.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Controllers/DW_PlayerController.h"
#include "Kismet/KismetMathLibrary.h"

void UDW_OverlayWidget::NativeConstruct()
{
    Super::NativeConstruct();

    PC = GetOwningPlayer<ADW_PlayerController>();
    if (!PC) return;

    PlayerChar = PC->GetPawn<ADW_BaseCharacter>();
    if (!PlayerChar && !PlayerChar->GetHealthComponent()) return;

    BindDelegates();
    InitializeHealthBarPercentage();
    InitializeCooldownBarPercentage();
    InitializeHealthText();
    SetCurrentAmmoText(FText::FromString(FString::FromInt(PlayerChar->GetCurrentAmmo())));
}

void UDW_OverlayWidget::BindDelegates()
{
    PlayerChar->GetHealthComponent()->HealthChangedDelegate.AddDynamic(this, &ThisClass::UpdateTextAndProgressBar);
    PlayerChar->AmmoChangedDelegate.AddDynamic(this, &ThisClass::UpdateCurrentAmmoText);
}

void UDW_OverlayWidget::TellPlayerThatEnemyHasSpawned()
{
    ++EnemyCount;
    SetEnemiesLeftText(FText::FromString(FString::FromInt(EnemyCount)));
}

void UDW_OverlayWidget::TellPlayerThatEnemyHasDied()
{
    --EnemyCount;
    SetEnemiesLeftText(FText::FromString(FString::FromInt(EnemyCount)));
}

void UDW_OverlayWidget::InitializeHealthBarPercentage()
{
    float HealthBarPercentage = PlayerChar->GetHealthComponent()->GetCurrentHealth() / PlayerChar->GetHealthComponent()->GetMaxHealth();
    SetHealthBarPercentage(HealthBarPercentage);
}

void UDW_OverlayWidget::InitializeCooldownBarPercentage()
{
    if (!PlayerChar) return;
    ShootCooldown->SetPercent(PlayerChar->GetFireRate());
}

void UDW_OverlayWidget::InitializeHealthText()
{
    CurrentHealth->SetText(FText::FromString(FString::FromInt(PlayerChar->GetHealthComponent()->GetCurrentHealth())));
    MaxHealth->SetText(FText::FromString(FString::FromInt(PlayerChar->GetHealthComponent()->GetMaxHealth())));
}

void UDW_OverlayWidget::UpdateTextAndProgressBar(float NewHealth)
{
    float HealthBarPercentage = NewHealth / PlayerChar->GetHealthComponent()->GetMaxHealth();

    SetHealthBarPercentage(HealthBarPercentage);
    SetCurrentHealthText(FText::FromString(FString::FromInt(NewHealth)));
}

void UDW_OverlayWidget::UpdateCurrentAmmoText(int32 NewAmmo)
{
    SetCurrentAmmoText(FText::FromString(FString::FromInt(NewAmmo)));
}

void UDW_OverlayWidget::UpdateShootProgressBar(float GetTimerRemaining)
{
    if (!PlayerChar) return;

    ShootCooldown->SetPercent(UKismetMathLibrary::SafeDivide(GetTimerRemaining, PlayerChar->GetFireRate()));
}

void UDW_OverlayWidget::SetHealthBarPercentage(float NewPercentage)
{
    HealthBar->SetPercent(NewPercentage);
}

void UDW_OverlayWidget::SetCurrentHealthText(const FText& NewText)
{
    CurrentHealth->SetText(NewText);
}

void UDW_OverlayWidget::SetCurrentAmmoText(const FText& NewText)
{
    CurrentAmmo->SetText(NewText);
}

void UDW_OverlayWidget::SetEnemiesLeftText(const FText& NewText)
{
    EnemiesLeft->SetText(NewText);
}

void UDW_OverlayWidget::SetCrosshairLocation(const FVector& Vector)
{
    UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(PC, Vector, TargetLocation, false);
    auto CrosshairSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(CrosshairSizeBox);
    auto SlotPosition = CrosshairSlot->GetPosition();

    TargetLocation = UKismetMathLibrary::Vector2DInterpTo(TargetLocation, SlotPosition, GetWorld()->DeltaTimeSeconds, 1.f);
    CrosshairSlot->SetPosition(TargetLocation);
}
