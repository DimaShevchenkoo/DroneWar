// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DW_MainMenuHUD.generated.h"

class UDW_MainMenuWidget;
class ADW_MainMenuController;

UCLASS()
class DRONEWARS_API ADW_MainMenuHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    UPROPERTY()
    ADW_MainMenuController* MMC;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> MainMenuWidgetClass;

    UPROPERTY()
    UDW_MainMenuWidget* MainMenuWidget;
};
