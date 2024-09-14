// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPGPROJECT_API UBaseActorComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	template <class T>
	T* GetOwnerPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Parameter from APawn");
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwnerPawn() const
	{
		return GetOwnerPawn<APawn>();
	}

	template<class T>
	T* GetOwnerController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' Paramer from AController");
		return GetOwnerPawn<APawn>()->GetController<T>();
	}
};
