// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DW_MainMenuController.generated.h"

UCLASS()
class DRONEWARS_API ADW_MainMenuController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
