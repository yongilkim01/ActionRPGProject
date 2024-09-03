// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Player/ActionRPGPlayerAnimInstance.h"
#include "Characters/ActionPlayerCharacter.h"

void UActionRPGPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (m_Character)
	{
		m_PlayerCharacter = Cast<AActionPlayerCharacter>(m_Character);
	}
}

void UActionRPGPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (m_HasAcceleration)
	{
		m_IdleElpasedTime = 0.f;
		m_IsRelax = false;
	}
	else
	{
		m_IdleElpasedTime += DeltaSeconds;

		m_IsRelax = (m_IdleElpasedTime >= m_RelaxThreasHold);
	}
}
