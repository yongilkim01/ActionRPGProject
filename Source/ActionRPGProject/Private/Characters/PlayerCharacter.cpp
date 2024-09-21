// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"

#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"

#include "DataAssets/Input/DataAsset_Input.h"
#include "DataAssets/StartUp/BaseStartUpDataAsset.h"
#include "Components/Input/ActionRPGInputComponent.h"
#include "Components/Combat/PlayerCombatComponent.h"

#include "ActionRPGGameplayTags.h"
#include "ActionRPGDebugHelper.h"

APlayerCharacter::APlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	springArm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm_->SetupAttachment(GetRootComponent());
	springArm_->TargetArmLength = 200.f;
	springArm_->SocketOffset = FVector(0.f, 55.f, 65.f);
	springArm_->bUsePawnControlRotation = true;

	camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera_->SetupAttachment(springArm_, USpringArmComponent::SocketName);
	camera_->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	playerCombatComponent_ = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("PlayerCombatComponent"));
}

UCombatComponent* APlayerCharacter::GetCombatComponent() const
{
	return playerCombatComponent_;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	checkf(inputDataAsset_, TEXT("Not assign input data asset"));
	ULocalPlayer* localPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);
	check(subSystem);
	subSystem->AddMappingContext(inputDataAsset_->inputMappingContext_, 0);
	UActionRPGInputComponent* mainInputComponent = CastChecked<UActionRPGInputComponent>(playerInputComponent);

	// 인풋 메소드와 향상된 인풋 컴포넌트를 바인드
	mainInputComponent->BindNativeInputAction(inputDataAsset_, ActionRPGGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
	mainInputComponent->BindNativeInputAction(inputDataAsset_, ActionRPGGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::InputLook);

	mainInputComponent->BindAbilityInputAction(inputDataAsset_, this, &ThisClass::InputAbilityPressed, &ThisClass::InputAbilityReleased);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!characterStartUpData_.IsNull())
	{
		if (UBaseStartUpDataAsset* LoadedData = characterStartUpData_.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(characterAbilitySystemComponent_);
		}
	}
}

void APlayerCharacter::InputMove(const FInputActionValue& inputActionValue)
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

void APlayerCharacter::InputLook(const FInputActionValue& inputActionValue)
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

void APlayerCharacter::InputAbilityPressed(FGameplayTag inputTag)
{
	Debug::PrintDebugMessage("ability pressed");
	// 어빌리티 시스템 컴포넌트의 기능 메소드 호출
	characterAbilitySystemComponent_->OnInputAbilityPressed(inputTag);
}

void APlayerCharacter::InputAbilityReleased(FGameplayTag inputTag)
{
	// 어빌리티 시스템 컴포넌트의 기능 메소드 호출
	characterAbilitySystemComponent_->OnInputAbilityReleased(inputTag);
}
