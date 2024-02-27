// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DW_PlayerWonWidget.generated.h"

class UButton;
class UTextBlock;
class UBackgroundBlur;

UCLASS()
class DRONEWARS_API UDW_PlayerWonWidget : public UUserWidget
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
    UTextBlock* YouWonText;

    UPROPERTY(meta=(BindWidgetAnim), Transient)
    UWidgetAnimation* BlurAnim;

    UPROPERTY(meta=(BindWidget))
    UButton* ExitToMenuButton;
};
