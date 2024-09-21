// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/BaseCombatInterface.h"
#include "BaseCharacter.generated.h"

class UActionRPGAbilitySystemComponent;
class UActionRPGAttributeSet;
class UBaseStartUpDataAsset;

/**
 * ABaseCharacter 클래스는 게임 캐릭터의 기본 기능을 구현합니다.
 * 이 클래스는 Ability System과 Combat Interface를 포함하여,
 * 캐릭터의 능력과 전투 관련 기능을 제공.
 */

UCLASS()
class ACTIONRPGPROJECT_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public IBaseCombatInterface
{
	GENERATED_BODY()

public: // Public method
	ABaseCharacter();

	/**
	 * Ability System Component를 반환하는 메소드.
	 * IAbilitySystemInterface의 상속 메소드.
	 * @return UAbilitySystemComponent* - 캐릭터의 Ability System Component
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/**
	 * Combat Component를 반환하는 메소드.
	 * IBaseCombatInterface의 상속 메소드
	 * @return UCombatComponent* - 캐릭터의 Combat Component
	 */
	virtual UCombatComponent* GetCombatComponent() const override;

protected:
	/**
	 * 새로운 컨트롤러에 의해 캐릭터가 소유될 때 호출됩니다.
	 * @param NewController - 캐릭터를 소유할 새로운 컨트롤러
	 */
	virtual void PossessedBy(AController* NewController) override;

public: // Geteer Setter
	/**
	 * Action RPG Ability System Component를 반환하는 인라인 함수
	 * @return UActionRPGAbilitySystemComponent* - 캐릭터의 Ability System Component
	 */
	FORCEINLINE UActionRPGAbilitySystemComponent* GetActionRPGAbilitySystemComponent() const { return characterAbilitySystemComponent_; }

	/**
	 * Action RPG Attribute Set을 반환하는 인라인 함수
	 * @return UActionRPGAttributeSet* - 캐릭터의 Attribute Set
	 */
	FORCEINLINE UActionRPGAttributeSet* GetActionRPGAttributesSet() const { return characterAttributeSet_; }

protected: // Protected variables
	/**
	 * 캐릭터의 Ability System Component
	 * 블루프린트에서 읽기 가능하지만 수정할 수 없는 속성.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UActionRPGAbilitySystemComponent* characterAbilitySystemComponent_;

	/**
	 * 캐릭터의 Attribute Set
	 * 블루프린트에서 읽기 가능하지만 수정할 수 없는 속성.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UActionRPGAttributeSet* characterAttributeSet_;

	/**
	 * 캐릭터의 시작 데이터를 정의하는 Asset의 참조
	 * 블루프린트에서 읽기 가능하며 수정할 수 없는 속성.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UBaseStartUpDataAsset> characterStartUpData_;

};
