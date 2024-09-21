// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "AbilitySystem/ActionRPGAttributeSet.h"

ABaseCharacter::ABaseCharacter()
{
	// Tick 기능 비활성화
	PrimaryActorTick.bCanEverTick = false;
	// Tick 시작 시 활성화하지 않음
	PrimaryActorTick.bStartWithTickEnabled = false;

	// 메쉬에서 데칼 수신 비활성화
	GetMesh()->bReceivesDecals = false;

	// 능력 시스템 컴포넌트 및 속성 세트 생성
	characterAbilitySystemComponent_ = CreateDefaultSubobject<UActionRPGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	characterAttributeSet_ = CreateDefaultSubobject<UActionRPGAttributeSet>(TEXT("Attributeset"));

}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	// Action RPG 능력 시스템 컴포넌트를 반환
	return GetActionRPGAbilitySystemComponent();
}

UCombatComponent* ABaseCharacter::GetCombatComponent() const
{
	return nullptr;
}

/*
 * PossessedBy 메서드: 능력 시스템 초기화
 * AI 또는 플레이어가 이 캐릭터를 소유할 때 호출됨
 */
void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// ASC가 있을 경우 초기화
	if (characterAbilitySystemComponent_)
	{
		// ASC에 캐릭터의 정보 초기화
		characterAbilitySystemComponent_->InitAbilityActorInfo(this, this);
		// 시작 데이터가 할당되지 않았는지 확인
		ensureMsgf(!characterStartUpData_.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}
