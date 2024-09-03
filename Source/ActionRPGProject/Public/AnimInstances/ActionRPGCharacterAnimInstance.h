// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ActionRPGAnimInstance.h"
#include "ActionRPGCharacterAnimInstance.generated.h"

class APlayerCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UActionRPGCharacterAnimInstance : public UActionRPGAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);

protected:
	UPROPERTY()
	APlayerCharacter* m_Character;

	UPROPERTY()
	UCharacterMovementComponent* m_CharacterMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimationData|LocomotionData")
	float m_GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimationData|LocomotionData")
	bool m_HasAcceleration;
	
};
