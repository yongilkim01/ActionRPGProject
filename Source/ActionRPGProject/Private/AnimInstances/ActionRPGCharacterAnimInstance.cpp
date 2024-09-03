// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ActionRPGCharacterAnimInstance.h"
#include "Characters/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UActionRPGCharacterAnimInstance::NativeInitializeAnimation()
{
	m_Character = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (m_Character)
	{
		m_CharacterMovementComponent = m_Character->GetCharacterMovement();
	}
}

void UActionRPGCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!m_Character || !m_CharacterMovementComponent)
	{
		return;
	}

	m_GroundSpeed = m_Character->GetVelocity().Size2D();

	m_HasAcceleration = m_CharacterMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}