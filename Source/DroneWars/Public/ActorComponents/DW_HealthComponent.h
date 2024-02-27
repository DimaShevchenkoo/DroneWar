// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DW_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DRONEWARS_API UDW_HealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDW_HealthComponent();

    UFUNCTION()
    void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

    virtual void BeginPlay() override;

    void AddScoreIfDamageCauserIsPlayer(AActor* DamageCauser);
    void SetCurrentHealth(const float NewHealth);

    FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
    FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

    FOnHealthChangedSignature HealthChangedDelegate;

protected:
    UPROPERTY(EditAnywhere)
    float MaxHealth = 100;
    float CurrentHealth;
};
