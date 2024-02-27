// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DW_BaseCharacter.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChangedSignature, int32, NewAmmo);

class ADW_PlayerController;
class ADW_Bullet;
class UDW_HealthComponent;
class UBoxComponent;
class UCameraComponent;

UCLASS()
class DRONEWARS_API ADW_BaseCharacter : public APawn
{
    GENERATED_BODY()

public:
    ADW_BaseCharacter();

    UFUNCTION()
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
        AActor* DamageCauser) override;

    UFUNCTION()
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    virtual void BeginPlay() override;
    virtual void Shoot();
    virtual void HandleShootCooldown();
    virtual void Destroyed() override;

    void RotateBarrelInRange(float TurnBarrelAxisValue);
    void UpdateCooldownProgressBar();

    FORCEINLINE int32 GetCurrentAmmo() const { return CurrentAmmo; }
    FORCEINLINE float GetFireRate() const { return FireRate; }
    FORCEINLINE UStaticMeshComponent* GetBodyMesh() const { return BodyMesh; }
    FORCEINLINE UDW_HealthComponent* GetHealthComponent() const { return HealthComponent; }

    FOnAmmoChangedSignature AmmoChangedDelegate;

protected:
    UPROPERTY(EditAnywhere)
    UBoxComponent* BoxCollision;

    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* BodyMesh;

    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* BarrelMesh;

    UPROPERTY(EditAnywhere)
    USceneComponent* BulletSpawnPoint;

    UPROPERTY(EditAnywhere)
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere)
    TSubclassOf<ADW_Bullet> BulletClass;

    UPROPERTY(EditAnywhere)
    UDW_HealthComponent* HealthComponent;

    UPROPERTY()
    ADW_PlayerController* PC;

    UPROPERTY(EditAnywhere)
    USoundBase* DeathSound;

    UPROPERTY(EditAnywhere)
    USoundBase* ShootSound;

    UPROPERTY(EditAnywhere)
    UNiagaraSystem* ShootNiagara;

    UPROPERTY(EditAnywhere)
    float BarrelPitchRotationMax = 5.f;

    UPROPERTY(EditAnywhere)
    float BarrelPitchRotationMin = -20.f;

    UPROPERTY(EditAnywhere)
    float FireRate = 2.f;

    UPROPERTY(EditAnywhere)
    int32 MaxAmmo = 30;
    int32 CurrentAmmo = 30;

    FTimerHandle ShootTimer;
    FTimerHandle UpdateCooldownProgressBarTimer;

    bool bCanShoot = true;
};
