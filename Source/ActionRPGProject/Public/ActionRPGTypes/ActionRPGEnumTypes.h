#pragma once

UENUM()
enum class EActionRPGConfirmType : uint8
{
	EAC_Yes,
	EAC_No
};

UENUM()
enum class EActionRPGValidType : uint8
{
	EAV_Valid,
	EAV_InValid
};

UENUM()
enum class EActionRPGSuccessType : uint8
{
	EAS_Successful,
	EAS_Failed
};