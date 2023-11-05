#pragma once
#include "CoreTypes.generated.h"

UENUM(BlueprintType)
enum class EMatchState:uint8
{
	WaitingToStart=0,
	InProgress,
	Pause,
	GameOver
};
