// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorComponents/DW_HealthComponent.h"
#include "Characters/DW_PlayerCharacter.h"
#include "Characters/DW_PlayerState.h"

UDW_HealthComponent::UDW_HealthComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UDW_HealthComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = MaxHealth;

    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &ThisClass::DamageTaken);

    HealthChangedDelegate.Broadcast(CurrentHealth);
}

void UDW_HealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
    AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.f) return;

    CurrentHealth -= Damage;

    HealthChangedDelegate.Broadcast(CurrentHealth);

    if (CurrentHealth <= 0)
    {
        AddScoreIfDamageCauserIsPlayer(DamageCauser);
        DamagedActor->Destroy();
    }
}

void UDW_HealthComponent::AddScoreIfDamageCauserIsPlayer(AActor* DamageCauser)
{
    if (!DamageCauser) return;

    if (auto P = Cast<ADW_PlayerCharacter>(DamageCauser))
    {
        auto PS = P->GetPlayerState<ADW_PlayerState>();
        if (!PS) return;

        PS->AddKillScore(1);
    }
}

void UDW_HealthComponent::SetCurrentHealth(const float NewHealth)
{
    CurrentHealth = NewHealth;
    HealthChangedDelegate.Broadcast(CurrentHealth);
}
