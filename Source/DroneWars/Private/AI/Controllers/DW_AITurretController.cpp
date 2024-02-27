// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Controllers/DW_AITurretController.h"
#include "Characters/DW_EnemyCharacter.h"

void ADW_AITurretController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	EnemyChar = Cast<ADW_EnemyCharacter>(InPawn);
}

void ADW_AITurretController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (InFireRange())
	{
		RotateTowerToPlayer();
		RotateBarrelToPlayer();
		if (CheckIfNothingIsBlockingVisibility())
		{
			Shoot();
		}
	}
}

bool ADW_AITurretController::CheckIfNothingIsBlockingVisibility()
{
	if (EnemyChar->CheckIfNothingIsBlockingVisibility())
	{
		return true;
	}
	return false;
}

bool ADW_AITurretController::InFireRange()
{
	if (!EnemyChar) return false;
	if (EnemyChar->CheckIfPlayerInFireRange()) return true;

	return false;
}

void ADW_AITurretController::RotateTowerToPlayer()
{ 
	if (!EnemyChar) return;
	EnemyChar->RotateTowerToPlayer();
}

void ADW_AITurretController::RotateBarrelToPlayer()
{
	if (!EnemyChar) return;
	EnemyChar->RotateBarrelToPlayer();
}

void ADW_AITurretController::Shoot()
{
	if (!EnemyChar) return;
	EnemyChar->Shoot();
}
