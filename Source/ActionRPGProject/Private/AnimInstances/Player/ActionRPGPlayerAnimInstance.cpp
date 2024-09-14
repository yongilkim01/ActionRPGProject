// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Player/ActionRPGPlayerAnimInstance.h"
#include "Characters/PlayerCharacter.h"

void UActionRPGPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (character_)
	{
		playerCharacter_ = Cast<APlayerCharacter>(character_);
	}
}

void UActionRPGPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (isAction_)
	{
		idleTime_ = 0.f;
		isRelax_ = false;
	}
	else
	{
		idleTime_ += DeltaSeconds;

		isRelax_ = (idleTime_ >= relaxThreasHold_);
	}
}
