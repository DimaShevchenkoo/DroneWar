// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DW_PlayerLostWidget.generated.h"

class UButton;
class UTextBlock;
class UBackgroundBlur;

UCLASS()
class DRONEWARS_API UDW_PlayerLostWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

protected:
    UFUNCTION()
    void ExitToMenu();

    UPROPERTY(meta=(BindWidget))
    UBackgroundBlur* BackgroundBlur;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* YouLostText;

    UPROPERTY(meta=(BindWidgetAnim), Transient)
    UWidgetAnimation* BlurAnim;

    UPROPERTY(meta=(BindWidget))
    UButton* ExitToMenuButton;
};
