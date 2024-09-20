// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAssets/StartUp/EnemyStartUpDataAsset.h"
#include "Engine/AssetManager.h"

#include "ActionRPGDebugHelper.h"

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

void AEnemyCharacter::PossessedBy(AController* inController)
{
	// 부모 클래스의 PossessedBy 메소드 호출
	Super::PossessedBy(inController);

	// 적 캐릭터의 초기화 데이터를 설정하는 메소드 호출
	InitEnemyStartUpData();
}

void AEnemyCharacter::InitEnemyStartUpData()
{
	// 초기화 데이터가 유효하지 않으면 함수 종료
	if (characterStartUpData_.IsNull()) return;


	/**
	* 비동기 방식으로 초기화 데이터를 로드 요청
	* 데이터가 필요할 때 즉시 로드하지 않고, 나중에 필요할 때 자동으로 로드하는 함수
	*/
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		characterStartUpData_.ToSoftObjectPath(), // 로드할 소프트 오브젝트 경로
		FStreamableDelegate::CreateLambda(
			[this]() // 로드 완료 후 호출될 람다 함수
			{
				// 로드된 데이터가 유효하면
				if (UBaseStartUpDataAsset* loadedData = characterStartUpData_.Get())
				{
					// 초기화 데이터를 Ability System Component에 적용
					loadedData->GiveToAbilitySystemComponent(characterAbilitySystemComponent_);

					// 디버그 메시지 출력: 초기화 데이터 로드 완료
					Debug::PrintDebugMessage(TEXT("Enemy start up data loaded"), FColor::Green);
				}
			}
		)
	);
}