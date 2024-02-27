// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/DW_EnemyHealthBarWidget.h"

#include "ActorComponents/DW_HealthComponent.h"
#include "Characters/DW_EnemyCharacter.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

void UDW_EnemyHealthBarWidget::NativeConstruct()
{
    Super::NativeConstruct();

    InitializeHealthBarPercentage();
}

void UDW_EnemyHealthBarWidget::InitializeHealthBarPercentage()
{
    if (!EnemyChar) return;

    HealthBar->SetPercent(EnemyChar->GetHealthComponent()->GetCurrentHealth() / EnemyChar->GetHealthComponent()->GetMaxHealth());
}

void UDW_EnemyHealthBarWidget::BindHealth(ADW_EnemyCharacter* OwnerChar)
{
    if (!OwnerChar) return;
    EnemyChar = OwnerChar;
    EnemyChar->GetHealthComponent()->HealthChangedDelegate.AddDynamic(this, &ThisClass::SetHealthBarPercentage);
}

void UDW_EnemyHealthBarWidget::SetHealthBarPercentage(float NewValue)
{
    HealthBar->SetPercent(UKismetMathLibrary::SafeDivide(NewValue, EnemyChar->GetHealthComponent()->GetMaxHealth()));
}
