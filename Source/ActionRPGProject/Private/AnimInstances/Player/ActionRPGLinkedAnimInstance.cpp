// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Player/ActionRPGLinkedAnimInstance.h"
#include "AnimInstances//Player/ActionRPGPlayerAnimInstance.h"

UActionRPGPlayerAnimInstance* UActionRPGLinkedAnimInstance::GetPlayerAnimInstance() const
{
	return Cast<UActionRPGPlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
