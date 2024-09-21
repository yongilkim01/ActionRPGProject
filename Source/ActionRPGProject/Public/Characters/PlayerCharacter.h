// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/BaseCharacter.h"
#include "GameplayTagContainer.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_Input;
struct FInputActionValue;
class UPlayerCombatComponent;

UCLASS()
class ACTIONRPGPROJECT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual UCombatComponent* GetCombatComponent() const override;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent*) override;
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

private:
	// Control player input method
	void InputMove(const FInputActionValue&);
	void InputLook(const FInputActionValue&);

	// Ability input method
	void InputAbilityPressed(FGameplayTag inputTag);
	void InputAbilityReleased(FGameplayTag inputTag);

private:

	/*
	* Component varialbes
	*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* springArm_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* camera_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UPlayerCombatComponent* playerCombatComponent_;


	/*
	* Input varialbes
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_Input* inputDataAsset_;

public: // Getter Setter
	FORCEINLINE UPlayerCombatComponent* GetPlayerCombatComponent() const { return playerCombatComponent_; }

};
