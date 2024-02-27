// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/DW_PlayerState.h"

void ADW_PlayerState::AddKillScore(int32 ScoreToAdd)
{
    ScoreAddedDelegate.Broadcast();
    KillScore += ScoreToAdd;
}
