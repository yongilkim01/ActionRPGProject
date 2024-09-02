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
}