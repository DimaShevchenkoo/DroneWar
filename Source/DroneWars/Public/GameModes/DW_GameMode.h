// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DW_GameMode.generated.h"

class ADW_PlayerState;

UCLASS()
class DRONEWARS_API ADW_GameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    UFUNCTION()
    void CheckIfPlayerWon();

    void TellGMThatEnemyHasSpawned();
    virtual void BeginPlay() override;

protected:
    int32 ScoreForWin;
    int32 LocalScore = 0;

    UPROPERTY()
    ADW_PlayerState* PS;
};
