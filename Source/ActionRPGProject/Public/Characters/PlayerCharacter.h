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

/**
 * APlayerCharacter 클래스는 플레이어 캐릭터의 기능을 구현합니다.
 * ABaseCharacter를 상속받아 기본적인 캐릭터 기능을 확장합니다.
 */
UCLASS()
class ACTIONRPGPROJECT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public: // public method
	APlayerCharacter();

	/**
	 * Combat Component를 반환합니다.
	 * ABaseCharacter의 GetCombatComponent 메서드를 오버라이드합니다.
	 * @return UCombatComponent* - 플레이어의 Combat Component
	 */
	virtual UCombatComponent* GetCombatComponent() const override;

protected: // protected method
	/**
	 * 플레이어 입력을 설정하는 메서드
	 * @param InputComponent - 입력 컴포넌트
	 */
	virtual void SetupPlayerInputComponent(class UInputComponent*) override;

	/**
	 * 게임 시작 시 호출되는 메서드
	 * 캐릭터의 초기화 작업을 수행합니다.
	 */
	virtual void BeginPlay() override;

	/**
	 * 새로운 컨트롤러에 의해 플레이어 캐릭터가 소유될 때 호출됩니다.
	 * @param NewController - 캐릭터를 소유할 새로운 컨트롤러
	 */
	virtual void PossessedBy(AController* NewController) override;

private: // private method
	/**
	 * 플레이어의 이동 입력을 처리하는 메서드
	 * @param ActionValue - 이동 입력 값
	 */
	void InputMove(const FInputActionValue&);
	/**
	 * 플레이어의 시선 입력을 처리하는 메서드
	 * @param ActionValue - 시선 입력 값
	 */
	void InputLook(const FInputActionValue&);
	/**
	 * 능력 입력이 눌렸을 때 호출되는 메서드
	 * @param inputTag - 능력 태그
	 */
	void InputAbilityPressed(FGameplayTag inputTag);
	/**
	 * 능력 입력이 해제되었을 때 호출되는 메서드
	 * @param inputTag - 능력 태그
	 */
	void InputAbilityReleased(FGameplayTag inputTag);

public: // Getter Setter
	/**
	 * 플레이어 전투 컴포넌트를 반환하는 인라인 함수
	 * @return UPlayerCombatComponent* - 플레이어의 전투 컴포넌트
	 */
	FORCEINLINE UPlayerCombatComponent* GetPlayerCombatComponent() const { return playerCombatComponent_; }

private: 
	/**
	 * 카메라 스프링 암 컴포넌트
	 * 블루프린트에서 읽기 가능하지만 수정할 수 없는 속성.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* springArm_;
	/**
	 * 카메라 컴포넌트
	 * 블루프린트에서 읽기 가능하지만 수정할 수 없는 속성.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* camera_;
	/**
	 * 플레이어 전투 컴포넌트
	 * 블루프린트에서 읽기 가능하지만 수정할 수 없는 속성.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UPlayerCombatComponent* playerCombatComponent_;
	/**
	 * 플레이어 입력 데이터 자산
	 * 블루프린트에서 읽기 가능하지만 수정할 수 없는 속성.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_Input* inputDataAsset_;
};
