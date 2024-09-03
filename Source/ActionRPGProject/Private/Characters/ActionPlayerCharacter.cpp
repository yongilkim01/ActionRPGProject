// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ActionPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"

#include "DataAssets/Input/DataAsset_Input.h"
#include "Components/Input/ActionRPGInputComponent.h"

#include "ActionRPGGameplayTags.h"
#include "ActionRPGDebugHelper.h"

AActionPlayerCharacter::AActionPlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_SpringArm->SetupAttachment(GetRootComponent());
	m_SpringArm->TargetArmLength = 200.f;
	m_SpringArm->SocketOffset = FVector(0.f, 55.f, 65.f);
	m_SpringArm->bUsePawnControlRotation = true;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Camera->SetupAttachment(m_SpringArm, USpringArmComponent::SocketName);
	m_Camera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void AActionPlayerCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	checkf(m_InputDataAsset, TEXT("Not assign input data asset"));
	ULocalPlayer* localPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);
	check(subSystem);
	subSystem->AddMappingContext(m_InputDataAsset->m_DefaultMappingContext, 0);
	UActionRPGInputComponent* mainInputComponent = CastChecked<UActionRPGInputComponent>(playerInputComponent);
	mainInputComponent->BindNativeInputAction(m_InputDataAsset, ActionRPGGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
	mainInputComponent->BindNativeInputAction(m_InputDataAsset, ActionRPGGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::InputLook);
}

void AActionPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Debug::PrintDebugMessage(TEXT("Working"));
}

void AActionPlayerCharacter::InputMove(const FInputActionValue& inputActionValue)
{
	const FVector2D moveVector = inputActionValue.Get<FVector2D>();
	const FRotator moveRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (moveVector.Y != 0.f)
	{
		const FVector forwardDir = moveRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(forwardDir, moveVector.Y);
	}

	if (moveVector.X != 0.f)
	{
		const FVector rightDir = moveRotation.RotateVector(FVector::RightVector);
		AddMovementInput(rightDir, moveVector.X);
	}
}

void AActionPlayerCharacter::InputLook(const FInputActionValue& inputActionValue)
{
	const FVector2D lookAxisVector = inputActionValue.Get<FVector2D>();

	if (lookAxisVector.X != 0.f)
	{
		AddControllerYawInput(lookAxisVector.X);
	}

	if (lookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(lookAxisVector.Y);
	}
}
