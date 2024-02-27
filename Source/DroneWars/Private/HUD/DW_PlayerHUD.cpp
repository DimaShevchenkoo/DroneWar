// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/DW_PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Controllers/DW_PlayerController.h"
#include "Widgets/DW_OverlayWidget.h"
#include "Widgets/DW_PlayerLostWidget.h"
#include "Widgets/DW_PlayerWonWidget.h"

void ADW_PlayerHUD::BeginPlay()
{
    Super::BeginPlay();

    if (!PlayerOverlayClass) return;

    PC = Cast<ADW_PlayerController>(GetOwningPlayerController());
    if (!PC) return;

    PlayerOverlayWidget = CreateWidget<UDW_OverlayWidget>(PC, PlayerOverlayClass);
    if (!PlayerOverlayWidget) return;

    PlayerOverlayWidget->AddToViewport();
}

void ADW_PlayerHUD::ShowShootCooldown(float GetTimerRemaining)
{
    if (!PlayerOverlayWidget) return;

    PlayerOverlayWidget->UpdateShootProgressBar(GetTimerRemaining);
}

void ADW_PlayerHUD::SetCrosshairLocation(const FVector& Vector)
{
    if (!PlayerOverlayWidget) return;
    PlayerOverlayWidget->SetCrosshairLocation(Vector);
}

void ADW_PlayerHUD::CreatePlayerWonWidget()
{
    PlayerWonWidget = CreateWidget<UDW_PlayerWonWidget>(PC, PlayerWonClass);
    if (!PlayerWonWidget) return;

    PlayerWonWidget->AddToViewport();
}

void ADW_PlayerHUD::CreatePlayerLostWidget()
{
    PlayerLostWidget = CreateWidget<UDW_PlayerLostWidget>(PC, PlayerLostClass);
    if (!PlayerLostWidget) return;

    PlayerLostWidget->AddToViewport();
}

void ADW_PlayerHUD::TellPlayerThatEnemyHasSpawned()
{
    if (!PlayerOverlayWidget) return;
    PlayerOverlayWidget->TellPlayerThatEnemyHasSpawned();
}

void ADW_PlayerHUD::TellPlayerThatEnemyHasDied()
{
    if (!PlayerOverlayWidget) return;
    PlayerOverlayWidget->TellPlayerThatEnemyHasDied();
}
