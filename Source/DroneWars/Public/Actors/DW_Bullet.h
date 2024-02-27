// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DW_Bullet.generated.h"

class UProjectileMovementComponent;

UCLASS()
class DRONEWARS_API ADW_Bullet : public AActor
{
    GENERATED_BODY()

public:
    ADW_Bullet();

    virtual void BeginPlay() override;

    void DestroyBullet();

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
        const FHitResult& HitResult);

protected:
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* BulletMesh;

    UPROPERTY(EditAnywhere)
    UProjectileMovementComponent* ProjectileMovementComponent;

    UPROPERTY(EditAnywhere)
    int32 BulletDamage = 10;

    UPROPERTY(EditAnywhere)
    float BulletLifeTime = 5.f;
};
