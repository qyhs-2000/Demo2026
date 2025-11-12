// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WuwaPlayerCharater.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "Components/WuwaEnhancedInputComponent.h"
#include "WarriorGameplayTags.h"
#include "DataAssets/DataAsset_RoleStartUp.h"

#include "AbilitySystem/WuwaAbilitySystemComponent.h"

AWuwaPlayerCharater::AWuwaPlayerCharater()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.f,55.f,65.f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,500.f,0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	OverrideInputComponentClass  = UWuwaEnhancedInputComponent::StaticClass();

	

}

void AWuwaPlayerCharater::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	checkf(SubSystem, TEXT("Subsystem is Null"));
	check(InputConfig->DefaultInputMappingContext);
	
	SubSystem->AddMappingContext(InputConfig->DefaultInputMappingContext, 0);
	
	UWuwaEnhancedInputComponent* WuwaInputComponent = CastChecked<UWuwaEnhancedInputComponent>(PlayerInputComponent);
	check(InputComponent);
	
	WuwaInputComponent->BindNativeInputAction(InputConfig, WuwaGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::InputLook);
	WuwaInputComponent->BindNativeInputAction(InputConfig, WuwaGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::InputMove);

	WuwaInputComponent->BindAbilityInputAction(InputConfig,this,&ThisClass::AbilityInputPressed,&ThisClass::AbilityInputReleased);
}

void AWuwaPlayerCharater::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!RoleStartUpData.IsNull())
	{
		if (UDataAsset_RoleStartUp* LoadedDataAsset = RoleStartUpData.LoadSynchronous())
		{
			LoadedDataAsset->GiveAbilityToAbilitSystemComponent(WuwaAbilitySystemComponent);
		}
	}

}

void AWuwaPlayerCharater::InputLook(const FInputActionValue &InputValue)
{
	const FVector2D LookVector = InputValue.Get<FVector2D>();
	if (LookVector.X != 0)
	{
		AddControllerYawInput(LookVector.X);
	}

	if (LookVector.Y != 0)
	{
		AddControllerPitchInput(LookVector.Y);
	}
}

void AWuwaPlayerCharater::InputMove(const FInputActionValue &InputValue)
{
	const FVector2D MoveVector = InputValue.Get<FVector2D>();
	const FRotator MovementRotation = FRotator(0.f, GetController()->GetControlRotation().Yaw, 0.f);
	
	if (MoveVector.X != 0)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MoveVector.X);
		
	}

	if (MoveVector.Y != 0)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection,MoveVector.Y);
	}
	OnMoveInput.Broadcast();
}

void AWuwaPlayerCharater::AbilityInputPressed(FGameplayTag InputTag)
{
	WuwaAbilitySystemComponent->OnAbilityInputPressed(InputTag);
}

void AWuwaPlayerCharater::AbilityInputReleased(FGameplayTag InputTag)
{
	WuwaAbilitySystemComponent->OnAbilityInputReleased(InputTag);
}
