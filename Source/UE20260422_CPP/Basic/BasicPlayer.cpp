#include "BasicPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"

#include "Kismet/KismetMathLibrary.h"

ABasicPlayer::ABasicPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		FRotator(0, -90.0f, 0)
	);
}

void ABasicPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasicPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EIC)
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABasicPlayer::Move);
		EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABasicPlayer::Look);
		EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ABasicPlayer::Jump);
		EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ABasicPlayer::StopJumping);
		EIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &ABasicPlayer::StopJumping);
	}
}

void ABasicPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	FRotator ControllerRotation = GetControlRotation();
	FRotator CameraRotation = FRotator(0, ControllerRotation.Yaw, 0);
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(CameraRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(CameraRotation);

	AddMovementInput(ForwardVector * MovementVector.X);
	AddMovementInput(RightVector  * MovementVector.Y);
}

void ABasicPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookVector.Y);
	AddControllerYawInput(LookVector.X);
}