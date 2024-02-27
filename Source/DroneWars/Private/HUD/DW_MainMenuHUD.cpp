// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/DW_MainMenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "Controllers/DW_MainMenuController.h"
#include "Widgets/DW_MainMenuWidget.h"

void ADW_MainMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (!MainMenuWidgetClass) return;

    MMC = Cast<ADW_MainMenuController>(GetOwningPlayerController());
    if (!MMC) return;

    MainMenuWidget = CreateWidget<UDW_MainMenuWidget>(MMC, MainMenuWidgetClass);
    if (!MainMenuWidget) return;

    MainMenuWidget->AddToViewport();
}
