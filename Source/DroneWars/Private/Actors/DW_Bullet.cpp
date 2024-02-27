// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DW_Bullet.h"

#include "Characters/DW_EnemyCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ADW_Bullet::ADW_Bullet()
{
    PrimaryActorTick.bCanEverTick = true;

    BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("Bullet Mesh");
    BulletMesh->SetupAttachment(GetRootComponent());

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
}

void ADW_Bullet::BeginPlay()
{
    Super::BeginPlay();

    BulletMesh->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);

    FTimerHandle BulletLifeTimeTimer;
    GetWorldTimerManager().SetTimer(BulletLifeTimeTimer, this, &ThisClass::DestroyBullet, BulletLifeTime);
}

void ADW_Bullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& HitResult)
{
    if (!OtherActor && OtherActor != GetOwner()) return;

    UGameplayStatics::ApplyDamage(OtherActor, BulletDamage, GetInstigatorController(), GetOwner(), UDamageType::StaticClass());

    DestroyBullet();
}

void ADW_Bullet::DestroyBullet()
{
    Destroy();
}
