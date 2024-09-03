// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ActionRPGCharacterAnimInstance.h"
#include "ActionRPGPlayerAnimInstance.generated.h"

class AActionPlayerCharacter;
/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UActionRPGPlayerAnimInstance : public UActionRPGCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimationData|Refrences")
	AActionPlayerCharacter* m_PlayerCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimationData|LocomotionData")
	bool m_IsRelax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimationData|LocomotionData")
	float m_RelaxThreasHold = 5.f;

	float m_IdleElpasedTime;
	
};
