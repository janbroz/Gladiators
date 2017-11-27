// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorController.h"
#include "Players/GladiatorPlayer.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

AGladiatorController::AGladiatorController()
{
	bShowMouseCursor = true;
}

void AGladiatorController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AlignToMouse();

}

void AGladiatorController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("HorizontalMovement", this, &AGladiatorController::MoveHorizontal);
	InputComponent->BindAxis("VerticalMovement", this, &AGladiatorController::MoveVertical);
}

void AGladiatorController::BeginPlay()
{
	Super::BeginPlay();

	GladiatorPawn = Cast<AGladiatorPlayer>(GetPawn());

}

void AGladiatorController::MoveHorizontal(float Amount)
{
	if (!GladiatorPawn) return;

	if (Amount != 0.f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Holi, moving horizontally"));
		//FVector Movement = GladiatorPawn->GetActorRightVector() * Amount;
		FVector Movement = FVector::RightVector * Amount;
		GladiatorPawn->GetCharacterMovement()->AddInputVector(Movement);
	}
}

void AGladiatorController::MoveVertical(float Amount)
{
	if (!GladiatorPawn) return;

	if (Amount != 0.f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Holi, moving vertically"));
		//FVector Movement = GladiatorPawn->GetActorForwardVector() * Amount;
		FVector Movement = FVector::ForwardVector * Amount;
		GladiatorPawn->GetCharacterMovement()->AddInputVector(Movement);
	}
}

void AGladiatorController::AlignToMouse()
{
	if (!GladiatorPawn) return;

	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, true, Hit);

	if (Hit.bBlockingHit)
	{
		FRotator NewRot = (Hit.Location - GladiatorPawn->GetActorLocation()).Rotation();
		FRotator LerpRot = FMath::Lerp(GladiatorPawn->GetActorRotation(), NewRot, 1.0f);

		float FTurn = FMath::FixedTurn(GladiatorPawn->GetActorRotation().Yaw, NewRot.Yaw, 0.5f);
		
		FRotator InterpRot = FMath::RInterpConstantTo(GladiatorPawn->GetActorRotation(), NewRot, GetWorld()->GetDeltaSeconds(), 300.f);

		SetControlRotation(FRotator(0.f, InterpRot.Yaw, 0.f));
		//GladiatorPawn->SetActorRotation(FRotator(0.f, FTurn, 0.f));
		//GladiatorPawn->SetActorRotation(FRotator(0.f, LerpRot.Yaw, 0.f));
		//GladiatorPawn->SetActorRotation(FRotator(0.f, NewRot.Yaw, 0.f));
	}
}