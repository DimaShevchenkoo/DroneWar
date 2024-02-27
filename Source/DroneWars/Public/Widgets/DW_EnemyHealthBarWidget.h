// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DW_EnemyHealthBarWidget.generated.h"

class ADW_EnemyCharacter;
class UProgressBar;
class USizeBox;

UCLASS()
class DRONEWARS_API UDW_EnemyHealthBarWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    void InitializeHealthBarPercentage();
    void BindHealth(ADW_EnemyCharacter* OwnerChar);

    UFUNCTION()
    void SetHealthBarPercentage(float NewValue);

protected:
    UPROPERTY(meta=(BindWidget))
    USizeBox* SizeBox;

    UPROPERTY(meta=(BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY()
    ADW_EnemyCharacter* EnemyChar;
};
