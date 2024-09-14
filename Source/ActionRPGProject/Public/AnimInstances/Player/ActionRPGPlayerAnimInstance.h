// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ActionRPGCharacterAnimInstance.h"
#include "ActionRPGPlayerAnimInstance.generated.h"

class APlayerCharacter;
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
	APlayerCharacter* playerCharacter_;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimationData|LocomotionData")
	bool isRelax_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimationData|LocomotionData")
	float relaxThreasHold_ = 5.f;

	float idleTime_;
	
};
