// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorPlayer.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "UnrealNetwork.h"

// Sets default values
AGladiatorPlayer::AGladiatorPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera arm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraArm->TargetArmLength = 1500.f;
	CameraArm->bDoCollisionTest = false;
	CameraArm->bAbsoluteRotation = true;
	CameraArm->bUsePawnControlRotation = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, CameraArm->SocketName);

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 300.f, 0.f);
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationRoll = false;
	//bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AGladiatorPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGladiatorPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGladiatorPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

