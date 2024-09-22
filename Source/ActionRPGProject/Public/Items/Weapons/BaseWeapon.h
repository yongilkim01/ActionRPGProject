// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class UBoxComponent;
/**
 * ABaseWeapon
 * 모든 무기의 기본 클래스로, 각 무기 객체는 ABaseWeapon을 상속.
 * 무기의 기본 메쉬와 충돌 박스를 관리.
 */

 /**
  * ABaseWeapon 클래스에서 사용되는 델리게이트 변수.
  * 무기가 타겟과 상호작용했을 때 호출되는 이벤트를 정의하며,
  * AActor* 타입의 매개변수를 전달받아 타겟 액터에 대한 정보를 제공한다.
  */
DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*);

UCLASS()
class ACTIONRPGPROJECT_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

protected: // Protected method
	/**
	 * OnCollisionBoxBeginOverlap
	 *
	 * 무기 충돌 박스가 다른 액터와 겹치기 시작할 때 호출되는 메소드.
	 * 겹쳐진 액터나 컴포넌트를 확인하고 필요한 로직을 수행하는데 사용.
	 *
	 * @param OverlappedComponent 충돌을 시작한 현재 무기의 충돌 박스
	 * @param OtherActor 충돌한 다른 액터
	 * @param OtherComp 충돌한 액터의 컴포넌트
	 * @param OtherBodyIndex 충돌한 컴포넌트의 인덱스
	 * @param bFromSweep 스윕 테스트에 의해 발생했는지 여부
	 * @param SweepResult 충돌과 관련된 상세 정보 (스윕 테스트의 경우)
	 */
	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/**
	 * OnCollisionBoxEndOverlap
	 *
	 * 무기 충돌 박스가 다른 액터와의 겹침이 끝났을 때 호출되는 메소드.
	 * 더 이상 충돌하지 않게 된 액터에 대해 필요한 로직을 수행하는데 사용.
	 *
	 * @param OverlappedComponent 충돌이 끝난 현재 무기의 충돌 박스
	 * @param OtherActor 더 이상 충돌하지 않게 된 액터
	 * @param OtherComp 더 이상 충돌하지 않는 액터의 컴포넌트
	 * @param OtherBodyIndex 충돌했던 컴포넌트의 인덱스
	 */
	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public: // Get Set
	/**
	 * 무기의 충돌 박스를 반환하는 인라인 함수.
	 * 외부에서 무기의 충돌 박스에 접근할 때 사용.
	 * @return weaponCollisionBox_ - 무기와 연결된 충돌 박스 컴포넌트
	 */
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return weaponCollisionBox_; }

public: // Public variables
	/**
	 * 무기가 타겟에 맞았을 때 호출되는 델리게이트.
	 * 이 델리게이트는 타겟 액터에 대한 포인터를 매개변수로 할당.
	 */
	FOnTargetInteractedDelegate onWeaponHitTarget_;
	/**
	 * 무기가 타겟에서 분리되었을 때 호출되는 델리게이트.
	 * 이 델리게이트는 타겟 액터에 대한 포인터를 매개변수로 할당.
	 */
	FOnTargetInteractedDelegate onWeaponPulledFromTarget_;

protected: // Private variables
	/**
	 * 무기의 스태틱 메쉬 컴포넌트
	 * 무기의 외형을 렌더링하는 데 사용.
	 * "Weapons" 카테고리에서 블루프린트와 상호작용 가능.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* weaponStaticMesh_;
	/**
	 * 무기 충돌을 감지하기 위한 박스 컴포넌트
	 * 무기가 공격할 때 충돌을 감지하는 역할.
	 * "Weapons" 카테고리에서 블루프린트와 상호작용 가능.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UBoxComponent* weaponCollisionBox_;
};
