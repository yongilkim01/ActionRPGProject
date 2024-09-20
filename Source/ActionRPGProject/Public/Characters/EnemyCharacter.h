// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class ACTIONRPGPROJECT_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

protected:
	// 전투 컴포넌트, 블루프린트에서 읽기 가능하며 수정할 수 없는 속성
	// "Combat" 카테고리에 속하는 컴포넌트로 표시
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* enemyCombatComponent_;

public:
	// 전투 컴포넌트 반환 인라인 함수
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return enemyCombatComponent_; }
};
