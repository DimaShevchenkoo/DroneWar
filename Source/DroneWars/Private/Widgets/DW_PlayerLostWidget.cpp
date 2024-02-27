// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/DW_PlayerLostWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UDW_PlayerLostWidget::NativeConstruct()
{
    Super::NativeConstruct();

    PlayAnimation(BlurAnim);

    ExitToMenuButton->OnClicked.AddDynamic(this, &ThisClass::ExitToMenu);
}

void UDW_PlayerLostWidget::ExitToMenu()
{
    UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}
