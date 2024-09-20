// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	// AI 소유 동작 설정: AI가 월드에 배치되거나 동적으로 스폰될 때 캐릭터를 소유
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 컨트롤러가 캐릭터의 피치(상하) 회전 제어를 하지 않도록 설정
	bUseControllerRotationPitch = false;
	// 컨트롤러가 캐릭터의 롤(좌우 기울기) 회전 제어를 하지 않도록 설정
	bUseControllerRotationRoll = false;
	// 컨트롤러가 캐릭터의 요(좌우 회전) 제어를 하지 않도록 설정
	bUseControllerRotationYaw = false;

	// 몬스터 이동 설정
	// 컨트롤러 기반의 회전 제어 비활성화
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	// 이동 방향에 따른 몬스터 회전 활성화
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 몬스터가 방향을 바꿀 때 회전 속도 설정
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	// 몬스터의 최대 걷기 속도 설정
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	// 몬스터가 걷는 중 멈출 때 제동 감속 설정
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;


	// 몬스터의 전투 컴포넌트 생성
	enemyCombatComponent_ =  CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");

}
