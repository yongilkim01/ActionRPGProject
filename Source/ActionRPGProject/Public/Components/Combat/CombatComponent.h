// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BaseActorComponent.h"
#include "GameplayTagContainer.h"
#include "CombatComponent.generated.h"

class ABaseWeapon;
/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API UCombatComponent : public UBaseActorComponent
{
	GENERATED_BODY()

public:
	// GameplayTag와 BaseWeapon을 map 객체에 등록하는 메소드
	UFUNCTION(BlueprintCallable, Category = "Character|Combat")
	void RegisterSpawnedWeapon(FGameplayTag RegistWeaponTag, ABaseWeapon* RegistWeapon, bool bEquip = false);

	// GameplayTag에 해당하는 BaseWeapon객체를 반환하는 메소드
	UFUNCTION(BlueprintCallable, Category = "Character|Combat")
	ABaseWeapon* GetCharacterWeaponByTag(FGameplayTag FindWeaponTag) const;

	// 현재 장착중인 BaseWeapon객체를 반환하는 메소드
	UFUNCTION(BlueprintCallable, Category = "Character|Combat")
	ABaseWeapon* GetCurrentEquippedWeapon() const;
public:
	// 현재 장착중인 BaseWeapon 객체의 해당하는 Tag 변수
	UPROPERTY(BlueprintReadWrite, Category = "Character|Combat")
	FGameplayTag currentEquippedWeaponTag_;

private:
	// BaseWeapon객체와 GameplayTag를 연결하는 map 변수
	TMap<FGameplayTag, ABaseWeapon*> characterWeaponMap_;
	
};
