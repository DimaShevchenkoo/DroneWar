// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DW_PlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreAddedSignature);

UCLASS()
class DRONEWARS_API ADW_PlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    void AddKillScore(int32 ScoreToAdd);

    FOnScoreAddedSignature ScoreAddedDelegate;

protected:
    int32 KillScore = 0;
};
