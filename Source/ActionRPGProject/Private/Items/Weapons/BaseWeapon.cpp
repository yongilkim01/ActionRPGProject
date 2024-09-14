// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/BaseWeapon.h"
#include "Components/BoxComponent.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	weaponStaticMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(weaponStaticMesh_);

	weaponCollisionBox_ = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	weaponCollisionBox_->SetupAttachment(GetRootComponent());
	weaponCollisionBox_->SetBoxExtent(FVector(20.f));
	weaponCollisionBox_->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}