// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/BaseWeapon.h"
#include "Components/BoxComponent.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	m_WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(m_WeaponMesh);

	m_WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	m_WeaponCollisionBox->SetupAttachment(GetRootComponent());
	m_WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	m_WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}