#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPC.generated.h"

class UInputMappingContext;

UCLASS()
class UE20260422_CPP_API ABasicPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Input Mapping Contexts
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<TSoftObjectPtr<UInputMappingContext>> IMC_Basics;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;
};
