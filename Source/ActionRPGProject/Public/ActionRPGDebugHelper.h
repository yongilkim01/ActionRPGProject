#pragma once

namespace Debug
{
	static void PrintDebugMessage(const FString& msg, const FColor& color = FColor::MakeRandomColor(), int32 inKey = -1)
	{
		if (GEngine) 
		{
			GEngine->AddOnScreenDebugMessage(inKey, 7.f, color, msg);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *msg);
		}
	}

	static void Print(const FString& FloatTitle, float FloatValueToPrint, int32 InKey = -1, const FColor& Color = FColor::MakeRandomColor())
	{
		if (GEngine)
		{
			const FString FinalMsg = FloatTitle + TEXT(": ") + FString::SanitizeFloat(FloatValueToPrint);
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, FinalMsg);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
		}
	}
}