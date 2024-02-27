// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/DW_PlayerCharacter.h"
#include "Actors/DW_Bullet.h"
#include "Controllers/DW_PlayerController.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

ADW_PlayerCharacter::ADW_PlayerCharacter()
{
    BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>("Barrel Mesh");
    BarrelMesh->SetupAttachment(BodyMesh);

    BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>("Bullet SpawnPoint");
    BulletSpawnPoint->SetupAttachment(BarrelMesh);

    PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Pawn Movement");
}

void ADW_PlayerCharacter::Shoot()
{
    if (!bCanShoot) return;

    if (CurrentAmmo > 0)
    {

        bCanShoot = false;

        if (!BulletClass) return;
        auto SpawnedActor = GetWorld()->SpawnActor<ADW_Bullet>(BulletClass, BulletSpawnPoint->GetComponentTransform());
        SpawnedActor->SetInstigator(this);
        SpawnedActor->SetOwner(this);

        --CurrentAmmo;

        AmmoChangedDelegate.Broadcast(CurrentAmmo);
        GetWorldTimerManager().SetTimer(ShootTimer, this, &ThisClass::HandleShootCooldown, FireRate);

        CalculateCooldownProgressBar();

        if (!ShootSound) return;
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, GetActorLocation(), GetActorRotation());
    }
}

void ADW_PlayerCharacter::CalculateCooldownProgressBar()
{
    PC = (PC) ? PC : Cast<ADW_PlayerController>(GetController());
    if (!PC) return;
    if (GetWorldTimerManager().TimerExists(ShootTimer))
    {
        GetWorldTimerManager().SetTimer(UpdateCooldownProgressBarTimer, this, &ThisClass::UpdateCooldownProgressBar, 0.01f, true, false);
    }
}

void ADW_PlayerCharacter::HandleShootCooldown()
{
    Super::HandleShootCooldown();
}

void ADW_PlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    CalculateAndSetCrosshairLocation();

    if (!GetWorldTimerManager().TimerExists(ShootTimer))
    {
        if (!PC) return;
        PC->ShowShootCooldown(FireRate);
    }
}

void ADW_PlayerCharacter::CalculateAndSetCrosshairLocation()
{
    FHitResult HitResult;
    FVector LineTraceStart = BulletSpawnPoint->GetComponentLocation();
    FVector LineTraceEnd = LineTraceStart + BulletSpawnPoint->GetForwardVector() * 50000.f;

    GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_WorldStatic);
    if (!PC) return;

    PC->SetCrosshairLocation(HitResult.Location);
}

void ADW_PlayerCharacter::Destroyed()
{
    if (!PC) return;

    PC->CreatePlayerLostWidget();

    PC->bShowMouseCursor = true;
    PC->SetInputMode(FInputModeUIOnly());

    Super::Destroyed();
}
