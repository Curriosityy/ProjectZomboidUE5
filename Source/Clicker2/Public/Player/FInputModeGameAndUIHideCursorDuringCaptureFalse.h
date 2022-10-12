#pragma once
#include "GameFramework/PlayerController.h"

struct FInputModeGameAndUIHideCursorDuringCaptureFalse : FInputModeGameAndUI
{
	FInputModeGameAndUIHideCursorDuringCaptureFalse()
	{
		bHideCursorDuringCapture = false;
	}
};
