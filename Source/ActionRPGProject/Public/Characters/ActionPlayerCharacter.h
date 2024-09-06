// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PlayerCharacter.h"
#include "ActionPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_Input;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API AActionPlayerCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	AActionPlayerCharacter();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent*) override;
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

private:
	void InputMove(const FInputActionValue&);
	void InputLook(const FInputActionValue&);
private:

#pragma region PlayerComponent
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* m_SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_Camera;

#pragma endregion

#pragma region PlayerInput

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_Input* m_InputDataAsset;
	

#pragma endregion
};
