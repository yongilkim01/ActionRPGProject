// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"

#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "AbilitySystem/ActionRPGAttributeSet.h"

APlayerCharacter::APlayerCharacter()
{
	// Base parent class
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	m_ActionRPGAbilitySystemComponent = CreateDefaultSubobject<UActionRPGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	m_ActionRPGAttributeSet = CreateDefaultSubobject<UActionRPGAttributeSet>(TEXT("Attributeset"));

}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return GetActionRPGAbilitySystemComponent();
}

/*
* PossessedBy method ability system method
*/
void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (m_ActionRPGAbilitySystemComponent)
	{
		m_ActionRPGAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!m_CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}
