// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/DW_MainMenuController.h"

void ADW_MainMenuController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;
    SetInputMode(FInputModeUIOnly());
}
