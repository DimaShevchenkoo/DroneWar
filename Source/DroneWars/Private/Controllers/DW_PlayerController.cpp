// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/DW_PlayerController.h"
#include "HUD/DW_PlayerHUD.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/DW_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void ADW_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (!Subsystem) return;

    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMappingContext, 0);

    if (!InputComponent) return;

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
        EnhancedInputComponent->BindAction(MoveUpwardsAction, ETriggerEvent::Triggered, this, &ThisClass::MoveUpwards);
        EnhancedInputComponent->BindAction(LookRightAction, ETriggerEvent::Triggered, this, &ThisClass::LookRight);
        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ThisClass::Shoot);
        EnhancedInputComponent->BindAction(TurnBarrelUpwardsAction, ETriggerEvent::Triggered, this, &ThisClass::TurnBarrelUpwards);
    }
}

void ADW_PlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    PlayerPawn = (PlayerPawn) ? PlayerPawn : GetPawn<ADW_PlayerCharacter>();
    PlayerHUD = (PlayerHUD) ? PlayerHUD : GetHUD<ADW_PlayerHUD>();
}

void ADW_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = false;
    SetInputMode(FInputModeGameOnly());
}

void ADW_PlayerController::ShowShootCooldown(float GetTimerRemaining)
{
    if (!PlayerHUD) return;

    PlayerHUD->ShowShootCooldown(GetTimerRemaining);
}

void ADW_PlayerController::SetCrosshairLocation(const FVector& Location)
{
    if (!PlayerHUD) return;

    PlayerHUD->SetCrosshairLocation(Location);
}

void ADW_PlayerController::CreatePlayerWonWidget()
{
    if (!PlayerHUD) return;
    PlayerHUD->CreatePlayerWonWidget();

    if (!WinSound) return;
    UGameplayStatics::PlaySound2D(GetWorld(), WinSound);
}

void ADW_PlayerController::CreatePlayerLostWidget()
{
    if (!PlayerHUD) return;
    PlayerHUD->CreatePlayerLostWidget();

    if (!LostSound) return;
    UGameplayStatics::PlaySound2D(GetWorld(), LostSound);
}

void ADW_PlayerController::TellPlayerThatEnemyHasSpawned()
{
    if (!PlayerHUD) return;
    PlayerHUD->TellPlayerThatEnemyHasSpawned();
}

void ADW_PlayerController::TellPlayerThatEnemyHasDied()
{
    if (!PlayerHUD) return;
    PlayerHUD->TellPlayerThatEnemyHasDied();
}

void ADW_PlayerController::Move(const FInputActionValue& Value)
{
    if (!PlayerPawn) return;
    const FVector2D MovementVector = Value.Get<FVector2D>();

    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    PlayerPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
    PlayerPawn->AddMovementInput(RightDirection, MovementVector.X);
}

void ADW_PlayerController::MoveUpwards(const FInputActionValue& Value)
{
    if (!PlayerPawn) return;
    const FVector2D MovementUpwards = Value.Get<FVector2D>();

    PlayerPawn->AddMovementInput(PlayerPawn->GetActorUpVector(), MovementUpwards.X);
}

void ADW_PlayerController::LookRight(const FInputActionValue& Value)
{
    const float LookAxisValue = Value.Get<float>();
    AddYawInput(LookAxisValue);
}

void ADW_PlayerController::TurnBarrelUpwards(const FInputActionValue& Value)
{
    if (!PlayerPawn) return;
    const float TurnBarrelAxisValue = Value.Get<float>();

    PlayerPawn->AddControllerPitchInput(TurnBarrelAxisValue);
    PlayerPawn->RotateBarrelInRange(TurnBarrelAxisValue);
}

void ADW_PlayerController::Shoot(const FInputActionValue& Value)
{
    if (!PlayerPawn) return;

    PlayerPawn->Shoot();
}
