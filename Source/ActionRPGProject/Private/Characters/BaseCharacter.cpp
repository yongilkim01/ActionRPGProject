// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "AbilitySystem/ActionRPGAttributeSet.h"

ABaseCharacter::ABaseCharacter()
{
	// Base parent class
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	characterAbilitySystemComponent_ = CreateDefaultSubobject<UActionRPGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	characterAttributeSet_ = CreateDefaultSubobject<UActionRPGAttributeSet>(TEXT("Attributeset"));

}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return GetActionRPGAbilitySystemComponent();
}

UCombatComponent* ABaseCharacter::GetCombatComponent() const
{
	return nullptr;
}

/*
* PossessedBy method ability system method
*/
void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (characterAbilitySystemComponent_)
	{
		characterAbilitySystemComponent_->InitAbilityActorInfo(this, this);

		ensureMsgf(!characterStartUpData_.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}
