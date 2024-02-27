// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/DW_GameMode.h"
#include "Characters/DW_PlayerState.h"
#include "Controllers/DW_PlayerController.h"
#include "Kismet/GameplayStatics.h"

void ADW_GameMode::BeginPlay()
{
    Super::BeginPlay();

    PS = Cast<ADW_PlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
    PS->ScoreAddedDelegate.AddDynamic(this, &ThisClass::CheckIfPlayerWon);
}

void ADW_GameMode::CheckIfPlayerWon()
{
    ++LocalScore;
    if (ScoreForWin == LocalScore)
    {
        auto PC = Cast<ADW_PlayerController>(PS->GetPlayerController());
        if (!PC) return;

        PC->CreatePlayerWonWidget();
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeUIOnly());
    }
}

void ADW_GameMode::TellGMThatEnemyHasSpawned()
{
    ++ScoreForWin;
}
