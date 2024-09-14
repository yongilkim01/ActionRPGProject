// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ActionRPGCharacterAnimInstance.h"
#include "Characters/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UActionRPGCharacterAnimInstance::NativeInitializeAnimation()
{
	character_ = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (character_)
	{
		characterMovementComponent_ = character_->GetCharacterMovement();
	}
}

void UActionRPGCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!character_ || !characterMovementComponent_)
	{
		return;
	}

	groundSpeed_ = character_->GetVelocity().Size2D();

	isAction_ = characterMovementComponent_->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}