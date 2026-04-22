#include "BasicPC.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void ABasicPC::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsLocalPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* InputSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		if (InputSystem)
		{
			InputSystem->ClearAllMappings();

			for (const auto& IMC : IMC_Basics)
			{
				if (IMC.IsValid())
				{
					InputSystem->AddMappingContext(IMC.LoadSynchronous(), 0);
				}
			}
		}
	}
}

void ABasicPC::OnUnPossess()
{
	Super::OnUnPossess();

	if (IsLocalPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* InputSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		if (InputSystem)
		{
			InputSystem->ClearAllMappings();
		}
	}
}
