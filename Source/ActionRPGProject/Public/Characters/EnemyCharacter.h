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

	virtual UCombatComponent* GetCombatComponent() const override;

protected:
	/**
	* AI가 이 적 캐릭터를 소유할 때 호출되는 함수
	* 이 메소드는 AI 컨트롤러가 캐릭터를 소유하고 제어하기 시작할 때 필요한 초기화 작업을 수행하는 데 사용
	* 적 캐릭터가 소유될 때 수행해야 할 특정 행동(예: 상태 초기화, AI의 행동 트리 설정 등)을 정의
	* inController: 소유하는 AI 컨트롤러
	*/
	virtual void PossessedBy(AController* inController) override;

private:
	// 시작 데이터 초기화 메소드
	void InitEnemyStartUpData();

protected:
	// 전투 컴포넌트, 블루프린트에서 읽기 가능하며 수정할 수 없는 속성
	// "Combat" 카테고리에 속하는 컴포넌트로 표시
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* enemyCombatComponent_;

public:
	// 전투 컴포넌트 반환 인라인 함수
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return enemyCombatComponent_; }
};
