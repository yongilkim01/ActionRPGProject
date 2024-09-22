// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/BaseWeapon.h"
#include "Components/BoxComponent.h"
#include "ActionRPGDebugHelper.h"

ABaseWeapon::ABaseWeapon()
{
	// 매 틱마다 호출되지 않도록 설정
	PrimaryActorTick.bCanEverTick = false;

	// 무기 스태틱 메쉬 컴포넌트를 생성하고 루트 컴포넌트로 설정
	weaponStaticMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(weaponStaticMesh_);
	// 무기 충돌 박스 컴포넌트를 생성하고 무기 메쉬에 연결
	weaponCollisionBox_ = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	weaponCollisionBox_->SetupAttachment(GetRootComponent());
	// 충돌 박스의 크기를 설정
	weaponCollisionBox_->SetBoxExtent(FVector(20.f));
	// 초기 상태에서 충돌을 비활성화
	weaponCollisionBox_->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// weaponCollisionBox_의 BeginOverlap 이벤트에 대해 OnCollisionBoxBeginOverlap 메소드를 바인딩
	// 충돌이 시작될 때마다 OnCollisionBoxBeginOverlap 함수가 호출됨
	weaponCollisionBox_->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	// weaponCollisionBox_의 EndOverlap 이벤트에 대해 OnCollisionBoxEndOverlap 메소드를 바인딩
	// 충돌이 끝날 때마다 OnCollisionBoxEndOverlap 함수가 호출됨
	weaponCollisionBox_->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);

}

void ABaseWeapon::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 무기를 소유하고 있는 캐릭터(소환된 Pawn)를 가져옴
	APawn* weaponOwningPawn = GetInstigator<APawn>();
	// 무기를 소유하고 있는 Pawn이 정상적으로 존재하는지 확인 (디버그용 메시지 출력)
	checkf(weaponOwningPawn, TEXT("check pawn object has a weapon class : %s"), *GetName());
	// 충돌한 액터가 Pawn인 경우
	if (APawn* hitPawn = Cast<APawn>(OtherActor))
	{
		// 충돌한 Pawn이 무기를 소유한 Pawn과 다른 경우 (즉, 적과 충돌했을 때)
		if (weaponOwningPawn != hitPawn)
		{
			// 무기 타겟과의 충돌 발생 시 델리게이트 호출
			onWeaponHitTarget_.ExecuteIfBound(OtherActor);
		}

		// TODO: Enemy character인지 확인 후 때리는 기능 구현 예정
	}
}

void ABaseWeapon::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// 무기를 소유하고 있는 캐릭터(소환된 Pawn)를 가져옴
	APawn* weaponOwningPawn = GetInstigator<APawn>();
	// 무기를 소유하고 있는 Pawn이 정상적으로 존재하는지 확인 (디버그용 메시지 출력)
	checkf(weaponOwningPawn, TEXT("check pawn object has a weapon class : %s"), *GetName());
	// 충돌한 액터가 Pawn인 경우
	if (APawn* hitPawn = Cast<APawn>(OtherActor))
	{
		// 충돌한 Pawn이 무기를 소유한 Pawn과 다른 경우 (즉, 적과의 충돌이 끝났을 때)
		if (weaponOwningPawn != hitPawn)
		{
			// 무기 타겟과의 충돌 종료 시 델리게이트 호출
			onWeaponPulledFromTarget_.ExecuteIfBound(OtherActor);
		}

		// TODO: Enemy character인지 확인 후 때리는 기능 구현 예정
	}
}
