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
#include "Components/RoleCombatComponent.h"
#include "Components/UI/RoleUIComponent.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/PostProcessComponent.h"

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

	RoleCombatComponent = CreateDefaultSubobject<URoleCombatComponent>(TEXT("RoleCombatComponent"));

	RoleUIComponent = CreateDefaultSubobject<URoleUIComponent>(TEXT("RoleUIComponent"));

	MatrixPostProcess = CreateDefaultSubobject<UPostProcessComponent>(TEXT("MatrixPostProcess"));
	MatrixPostProcess->SetupAttachment(RootComponent);
	MatrixPostProcess->bUnbound = true;
	MatrixPostProcess->bEnabled = false;
}

UPawnCombatComponent* AWuwaPlayerCharater::GetPawnCombatComponent() const
{
	return RoleCombatComponent;
}

UPawnUIComponent* AWuwaPlayerCharater::GetPawnUIComponent() const
{
	return RoleUIComponent;
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
	//WuwaInputComponent->BindNativeInputAction(InputConfig, WuwaGameplayTags::InputTag_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);

	WuwaInputComponent->BindNativeInputAction(InputConfig, WuwaGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTrigger);
	WuwaInputComponent->BindNativeInputAction(InputConfig, WuwaGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);

	WuwaInputComponent->BindAbilityInputAction(InputConfig,this,&ThisClass::AbilityInputPressed,&ThisClass::AbilityInputReleased);
}

void AWuwaPlayerCharater::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpBase* LoadedDataAsset = CharacterStartUpData.LoadSynchronous())
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

void AWuwaPlayerCharater::Input_SwitchTargetTrigger(const FInputActionValue& InputValue)
{
	SwitchDirection = InputValue.Get<FVector2D>();
}

void AWuwaPlayerCharater::Input_SwitchTargetCompleted(const FInputActionValue& InputValue)
{
	FGameplayEventData Data;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, SwitchDirection.X > 0 ? WuwaGameplayTags::Player_Event_SwitchTargetLock_Right : WuwaGameplayTags::Player_Event_SwitchTargetLock_Left,
		Data);
}

void AWuwaPlayerCharater::AbilityInputPressed(FGameplayTag InputTag)
{
	if (!InputTag.IsValid())
	{
		
		return;
	}

	if (WuwaAbilitySystemComponent)
	{
		WuwaAbilitySystemComponent->OnAbilityInputPressed(InputTag);
	}

	if(!HasAuthority())
	{
		ServerAbilityInputPressed(InputTag);
	}
}

void AWuwaPlayerCharater::AbilityInputReleased(FGameplayTag InputTag)
{
	if (WuwaAbilitySystemComponent)
	{
		WuwaAbilitySystemComponent->OnAbilityInputReleased(InputTag);
	}
}

bool AWuwaPlayerCharater::ServerAbilityInputPressed_Validate(FGameplayTag InputTag)
{
	return InputTag.IsValid();
}

void AWuwaPlayerCharater::ServerAbilityInputPressed_Implementation(FGameplayTag InputTag)
{
	if (WuwaAbilitySystemComponent)
	{
		WuwaAbilitySystemComponent->OnAbilityInputPressed(InputTag);
	}
}

void AWuwaPlayerCharater::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
	if(!WuwaAbilitySystemComponent)
	{
		return;
	}
	if(GetCharacterMovement()->IsFalling())
	{
		WuwaAbilitySystemComponent->AddLooseGameplayTag(WuwaGameplayTags::Shared_Status_Falling);
	}
	else
	{
		WuwaAbilitySystemComponent->RemoveLooseGameplayTag(WuwaGameplayTags::Shared_Status_Falling);
	}
}

void AWuwaPlayerCharater::BeginPlay()
{
	Super::BeginPlay();
	USkeletalMeshComponent* MeshComp = GetMesh();
	//if (MeshComp)
	//{
	//	// ��Ҫ��������ײ�ڿͻ���Ҳ��������
	//	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//	MeshComp->SetCollisionObjectType(ECC_Pawn);
	//	MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//	MeshComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	//	MeshComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	//	MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	//	MeshComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block);
	//	MeshComp->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Block);
	//	MeshComp->SetCollisionResponseToChannel(ECC_Destructible, ECR_Block);

	//	// ȷ������ͬ��
	//	MeshComp->SetIsReplicated(true);

	//	// ����Simulated Proxy��Ҳ������ײ�¼�
	//	if (GetLocalRole() == ROLE_SimulatedProxy)
	//	{
	//		MeshComp->SetGenerateOverlapEvents(true);
	//	}
	//}

	//// ���������
	//UCapsuleComponent* Capsule = GetCapsuleComponent();
	//if (Capsule)
	//{
	//	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//	Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	//	Capsule->SetIsReplicated(true);

	//	if (GetLocalRole() == ROLE_SimulatedProxy)
	//	{
	//		Capsule->SetGenerateOverlapEvents(true);
	//	}
	//}
}
