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
	// GameplayTag�� BaseWeapon�� map ��ü�� ����ϴ� �޼ҵ�
	UFUNCTION(BlueprintCallable, Category = "Character|Combat")
	void RegisterSpawnedWeapon(FGameplayTag RegistWeaponTag, ABaseWeapon* RegistWeapon, bool bEquip = false);

	// GameplayTag�� �ش��ϴ� BaseWeapon��ü�� ��ȯ�ϴ� �޼ҵ�
	UFUNCTION(BlueprintCallable, Category = "Character|Combat")
	ABaseWeapon* GetCharacterWeaponByTag(FGameplayTag FindWeaponTag) const;

	// ���� �������� BaseWeapon��ü�� ��ȯ�ϴ� �޼ҵ�
	UFUNCTION(BlueprintCallable, Category = "Character|Combat")
	ABaseWeapon* GetCurrentEquippedWeapon() const;
public:
	// ���� �������� BaseWeapon ��ü�� �ش��ϴ� Tag ����
	UPROPERTY(BlueprintReadWrite, Category = "Character|Combat")
	FGameplayTag currentEquippedWeaponTag_;

private:
	// BaseWeapon��ü�� GameplayTag�� �����ϴ� map ����
	TMap<FGameplayTag, ABaseWeapon*> characterWeaponMap_;
	
};
