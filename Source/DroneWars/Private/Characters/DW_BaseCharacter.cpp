// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/DW_BaseCharacter.h"
#include "ActorComponents/DW_HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Controllers/DW_PlayerController.h"
#include "Kismet/GameplayStatics.h"

ADW_BaseCharacter::ADW_BaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
    RootComponent = BoxCollision;

    BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Body Mesh");
    BodyMesh->SetupAttachment(GetRootComponent());

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
    CameraComponent->SetupAttachment(GetRootComponent());

    HealthComponent = CreateDefaultSubobject<UDW_HealthComponent>("Health Component");
}

void ADW_BaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    CurrentAmmo = MaxAmmo;

    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
}

float ADW_BaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
    AActor* DamageCauser)
{
    return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ADW_BaseCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this) return;

    if (OtherActor->ActorHasTag("Ammo"))
    {
        if (CurrentAmmo == MaxAmmo) return;

        CurrentAmmo = MaxAmmo;
        AmmoChangedDelegate.Broadcast(CurrentAmmo);
        OtherActor->Destroy();
    }
    if (OtherActor->ActorHasTag("Health"))
    {
        if (HealthComponent->GetCurrentHealth() == HealthComponent->GetMaxHealth()) return;

        HealthComponent->SetCurrentHealth(HealthComponent->GetMaxHealth());
        OtherActor->Destroy();
    }
}

void ADW_BaseCharacter::RotateBarrelInRange(float TurnBarrelAxisValue)
{
    float CurrentBarrelRotationPitch = BarrelMesh->GetRelativeRotation().Pitch;

    FRotator NewBarrelRotation = FRotator(TurnBarrelAxisValue, 0.f, 0.f);
    if ((CurrentBarrelRotationPitch >= BarrelPitchRotationMin && TurnBarrelAxisValue < 0.f) ||
        (CurrentBarrelRotationPitch <= BarrelPitchRotationMax && TurnBarrelAxisValue > 0.f))
    {
        BarrelMesh->AddLocalRotation(NewBarrelRotation, true);
    }
}

void ADW_BaseCharacter::Shoot()
{
}

void ADW_BaseCharacter::HandleShootCooldown()
{
    bCanShoot = true;
}

void ADW_BaseCharacter::Destroyed()
{
    Super::Destroyed();
    if (!DeathSound) return;
    UGameplayStatics::PlaySound2D(GetWorld(), DeathSound);
}

void ADW_BaseCharacter::UpdateCooldownProgressBar()
{
    if (!GetWorldTimerManager().TimerExists(ShootTimer)) return;

    PC->ShowShootCooldown(GetWorldTimerManager().GetTimerRemaining(ShootTimer));
}
