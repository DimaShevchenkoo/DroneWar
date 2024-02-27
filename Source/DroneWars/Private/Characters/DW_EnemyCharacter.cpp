// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/DW_EnemyCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "Actors/DW_Bullet.h"
#include "Characters/DW_PlayerCharacter.h"
#include "Components/WidgetComponent.h"
#include "Controllers/DW_PlayerController.h"
#include "GameModes/DW_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Widgets/DW_EnemyHealthBarWidget.h"

ADW_EnemyCharacter::ADW_EnemyCharacter()
{
    TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>("Tower Mesh");
    TowerMesh->SetupAttachment(BodyMesh);

    BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>("Barrel Mesh");
    BarrelMesh->SetupAttachment(TowerMesh);

    BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>("Bullet SpawnPoint");
    BulletSpawnPoint->SetupAttachment(BarrelMesh);

    HealthBar = CreateDefaultSubobject<UWidgetComponent>("Health Bar");
    HealthBar->SetupAttachment(GetRootComponent());
}

void ADW_EnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (!GetWorld()) return;
    PlayerChar = Cast<ADW_PlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    BindHealthToTheWidget();
    TellGMAndPlayerThatEnemyHasSpawned();
}

void ADW_EnemyCharacter::BindHealthToTheWidget()
{
    auto HealthBarWidget = Cast<UDW_EnemyHealthBarWidget>(HealthBar->GetWidget());
    if (!HealthBarWidget) return;
    HealthBarWidget->BindHealth(this);
}

void ADW_EnemyCharacter::TellGMAndPlayerThatEnemyHasSpawned()
{
    PC = PlayerChar->GetController<ADW_PlayerController>();
    if (!PC) return;

    PC->TellPlayerThatEnemyHasSpawned();
    ADW_GameMode* GM = Cast<ADW_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (!GM) return;

    GM->TellGMThatEnemyHasSpawned();
}

void ADW_EnemyCharacter::Shoot()
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

        GetWorldTimerManager().SetTimer(ShootTimer, this, &ThisClass::HandleShootCooldown, FireRate);

        if (!ShootSound) return;
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, GetActorLocation(), GetActorRotation());

        if (!ShootNiagara) return;
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ShootNiagara, BulletSpawnPoint->GetComponentLocation());
    }
}

void ADW_EnemyCharacter::Destroyed()
{
    if (!PC) return;

    PC->TellPlayerThatEnemyHasDied();
    Super::Destroyed();
}

void ADW_EnemyCharacter::RotateTowerToPlayer()
{
    if (!PlayerChar || !TowerMesh) return;

    FVector TargetLocation = PlayerChar->GetActorLocation() - TowerMesh->GetComponentLocation();
    FRotator TargetRotation{0.f, TargetLocation.Rotation().Yaw, 0.f};

    TowerMesh->SetWorldRotation(FMath::RInterpTo(TowerMesh->GetComponentRotation(), TargetRotation,
        GetWorld()->GetDeltaSeconds(), TowerRotationSpeed));
}

void ADW_EnemyCharacter::RotateBarrelToPlayer()
{
    FRotator TargetBarrelRotation = UKismetMathLibrary::FindLookAtRotation(
        TowerMesh->GetComponentLocation(), PlayerChar->GetBodyMesh()->GetComponentLocation());
    float TargetAngle = TargetBarrelRotation.Pitch - BarrelMesh->GetRelativeRotation().Pitch;
    if (CheckIfBarrelInAngleRange(TargetAngle))
    {
        BarrelMesh->AddRelativeRotation({TargetAngle, 0.f, 0.f});
    }
}

bool ADW_EnemyCharacter::CheckIfPlayerInFireRange()
{
    if (!PlayerChar) return false;

    float DistanceBetweenPlayerAndTurret = FVector::Dist(GetActorLocation(), PlayerChar->GetActorLocation());
    if (DistanceBetweenPlayerAndTurret <= FireRange)
    {
        return true;
    }
    return false;
}

bool ADW_EnemyCharacter::CheckIfBarrelInAngleRange(float CurrentAngle)
{
    float CurrentRotation = BarrelMesh->GetRelativeRotation().Pitch;
    if ((CurrentRotation >= BarrelPitchRotationMin && CurrentAngle < 0.f) ||
        (CurrentAngle <= BarrelPitchRotationMax && CurrentAngle > 0.f))
    {
        return true;
    }
    return false;
}

bool ADW_EnemyCharacter::CheckIfNothingIsBlockingVisibility()
{
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);

    FHitResult HitResult;

    FVector StartLineTrace = BulletSpawnPoint->GetComponentLocation();
    FVector EndLineTrace = StartLineTrace + (StartLineTrace.ForwardVector * 5000.f);

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLineTrace, EndLineTrace, ECC_WorldStatic);
    if (bHit) return true;
    return false;
}
