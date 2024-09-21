// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"

#include "AbilitySystem/ActionRPGAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"

#include "DataAssets/Input/DataAsset_Input.h"
#include "DataAssets/StartUp/BaseStartUpDataAsset.h"
#include "Components/Input/ActionRPGInputComponent.h"
#include "Components/Combat/PlayerCombatComponent.h"

#include "ActionRPGGameplayTags.h"
#include "ActionRPGDebugHelper.h"

APlayerCharacter::APlayerCharacter()
{
	// 캐릭터 캡슐 컴포넌트 초기화
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	// 컨트롤러의 회전 사용 비활성화
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 스프링 암 컴포넌트 생성 및 설정
	springArm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm_->SetupAttachment(GetRootComponent());
	springArm_->TargetArmLength = 200.f; // 카메라와의 거리 설정
	springArm_->SocketOffset = FVector(0.f, 55.f, 65.f); // 카메라 소켓 위치 설정
	springArm_->bUsePawnControlRotation = true; // 파운의 제어 회전 사용

	// 카메라 컴포넌트 생성 및 설정
	camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera_->SetupAttachment(springArm_, USpringArmComponent::SocketName); // 스프링 암에 부착
	camera_->bUsePawnControlRotation = false; // 파운의 제어 회전 사용 안 함

	// 캐릭터 이동 설정
	GetCharacterMovement()->bOrientRotationToMovement = true; // 이동 방향에 따라 회전
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); // 회전 속도 설정
	GetCharacterMovement()->MaxWalkSpeed = 400.f; // 최대 걷기 속도 설정
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; // 걷기 감속 설정

	// 플레이어 전투 컴포넌트 생성
	playerCombatComponent_ = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("PlayerCombatComponent"));
}

UCombatComponent* APlayerCharacter::GetCombatComponent() const
{
	// 플레이어 전투 컴포넌트를 반환
	return playerCombatComponent_;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	// 인풋 데이터 자산이 할당되었는지 확인
	checkf(inputDataAsset_, TEXT("Not assign input data asset"));
	ULocalPlayer* localPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);
	check(subSystem);
	// 인풋 매핑 컨텍스트 추가
	subSystem->AddMappingContext(inputDataAsset_->inputMappingContext_, 0);
	UActionRPGInputComponent* mainInputComponent = CastChecked<UActionRPGInputComponent>(playerInputComponent);

	// 인풋 메소드와 향상된 인풋 컴포넌트를 바인드
	mainInputComponent->BindNativeInputAction(inputDataAsset_, ActionRPGGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
	mainInputComponent->BindNativeInputAction(inputDataAsset_, ActionRPGGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::InputLook);

	mainInputComponent->BindAbilityInputAction(inputDataAsset_, this, &ThisClass::InputAbilityPressed, &ThisClass::InputAbilityReleased);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController); // 부모 클래스의 PossessedBy 호출

	// 시작 데이터가 할당되었는지 확인
	if (!characterStartUpData_.IsNull())
	{
		if (UBaseStartUpDataAsset* LoadedData = characterStartUpData_.LoadSynchronous())
		{
			// 능력 시스템 컴포넌트에 시작 데이터 적용
			LoadedData->GiveToAbilitySystemComponent(characterAbilitySystemComponent_);
		}
	}
}


void APlayerCharacter::InputMove(const FInputActionValue& inputActionValue)
{
	const FVector2D moveVector = inputActionValue.Get<FVector2D>(); // 입력 값에서 이동 벡터 가져오기
	const FRotator moveRotation(0.f, Controller->GetControlRotation().Yaw, 0.f); // 현재 컨트롤러의 회전 각도 가져오기

	if (moveVector.Y != 0.f)
	{
		const FVector forwardDir = moveRotation.RotateVector(FVector::ForwardVector); // 전방 방향 벡터 계산
		AddMovementInput(forwardDir, moveVector.Y); // 이동 입력 추가
	}

	if (moveVector.X != 0.f)
	{
		const FVector rightDir = moveRotation.RotateVector(FVector::RightVector); // 우측 방향 벡터 계산
		AddMovementInput(rightDir, moveVector.X); // 이동 입력 추가
	}
}

void APlayerCharacter::InputLook(const FInputActionValue& inputActionValue)
{
	const FVector2D lookAxisVector = inputActionValue.Get<FVector2D>(); // 입력 값에서 시점 조정 벡터 가져오기

	if (lookAxisVector.X != 0.f)
	{
		AddControllerYawInput(lookAxisVector.X); // Yaw 입력 추가
	}

	if (lookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(lookAxisVector.Y); // Pitch 입력 추가
	}
}

void APlayerCharacter::InputAbilityPressed(FGameplayTag inputTag)
{
	Debug::PrintDebugMessage("ability pressed"); // 디버그 메시지 출력
	// 어빌리티 시스템 컴포넌트의 기능 메소드 호출
	characterAbilitySystemComponent_->OnInputAbilityPressed(inputTag);
}

void APlayerCharacter::InputAbilityReleased(FGameplayTag inputTag)
{
	// 어빌리티 시스템 컴포넌트의 기능 메소드 호출
	characterAbilitySystemComponent_->OnInputAbilityReleased(inputTag);
}
