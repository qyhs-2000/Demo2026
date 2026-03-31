// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Role/GA_TargetLock.h"
#include "Controller/WuwaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Gameplay/Tasks/AbilityTask_ExecuteOnTick.h"
#include "Character/WuwaPlayerCharater.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "DebugHelper.h"
void UGA_TargetLock::OnAbilityActivate()
{
	debug::Print(TEXT("Target Lock Activate!"));
	TryLockTargetCharacter();
	if (!IsActive())
	{
		return;
	}
	InitTargetLockMovement();
	InitTargetLockInputMappingContext();
	ActivationOwnedTags.AddTag(WuwaGameplayTags::Player_Status_TargetLocking);
	UAbilityTask_ExecuteTaskOnTick* ExecuteTaskOnTick = UAbilityTask_ExecuteTaskOnTick::ExecuteTaskOnTick(this);
	ExecuteTaskOnTick->OnAbilityTaskTick.AddUniqueDynamic(this, &ThisClass::OnTargetLockTick);

	ExecuteTaskOnTick->ReadyForActivation();

	UAbilityTask_WaitGameplayEvent* WaitGameplayEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, WuwaGameplayTags::Player_Event_SwitchTargetLock, nullptr, false, false);
	WaitGameplayEventTask->EventReceived.AddUniqueDynamic(this, &ThisClass::OnSwitchTarget);
	WaitGameplayEventTask->ReadyForActivation();

}

void UGA_TargetLock::OnEndAbility()
{
	TargetLockWidget->RemoveFromParent();
	RemoveTargetLockInputMappingContext();
	ResetTargetLockMovement();
}

void UGA_TargetLock::InitTargetLockInputMappingContext()
{
	const ULocalPlayer* LocalPlayer = GetRoleControllerFromActorInfo()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(LocalPlayerSystem);
	LocalPlayerSystem->AddMappingContext(IMC_TargetLock, 3);
}

void UGA_TargetLock::RemoveTargetLockInputMappingContext()
{
	if (!GetRoleControllerFromActorInfo()) return;
	const ULocalPlayer* LocalPlayer = GetRoleControllerFromActorInfo()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(LocalPlayerSystem);
	LocalPlayerSystem->RemoveMappingContext(IMC_TargetLock);
}

void UGA_TargetLock::TryLockTargetCharacter()
{
	GetAvailableTargetLockActors();
	if (AvailableActors.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}
	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActors);
	if (CurrentLockedActor.IsValid())
	{
		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
	}
	else
	{
		CancelTargetLockAbility();
	}
}

void UGA_TargetLock::GetAvailableTargetLockActors()
{
	AvailableActors.Empty();
	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::BoxTraceMultiForObjects(GetRoleCharacterInfo(), GetRoleCharacterInfo()->GetActorLocation(),
		GetRoleCharacterInfo()->GetActorLocation() + GetRoleCharacterInfo()->GetActorForwardVector() * BoxTraceDistance,
		BoxTraceSize / 2,
		GetRoleCharacterInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Type::Persistent : EDrawDebugTrace::None,
		HitResults,
		true
	);

	for (const FHitResult& HitResult : HitResults)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			if (HitActor != GetRoleCharacterInfo())
			{
				AvailableActors.AddUnique(HitActor);
			}
		}
	}
}

void UGA_TargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

AActor* UGA_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float NearestDistance = 0.f;
	return UGameplayStatics::FindNearestActor(GetRoleCharacterInfo()->GetActorLocation(), InAvailableActors, NearestDistance);
}

void UGA_TargetLock::SetTargetLockWidgetPosition()
{
	if (!TargetLockWidget || !CurrentLockedActor.IsValid())
	{
		CancelTargetLockAbility();
		return;
	}

	FVector2D ScreenPosition;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetRoleControllerFromActorInfo(), CurrentLockedActor->GetActorLocation(), ScreenPosition, true);

	if (TargetLockBoxSize == FVector2D::ZeroVector)
	{
		TargetLockWidget->WidgetTree->ForEachWidget([this](UWidget* FoundWidget) {
			if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
			{
				TargetLockBoxSize.X = FoundSizeBox->GetWidthOverride();
				TargetLockBoxSize.Y = FoundSizeBox->GetHeightOverride();
			}
			});

	}
	ScreenPosition -= (TargetLockBoxSize / 2.f);
	TargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}

void UGA_TargetLock::InitTargetLockMovement()
{
	CachedMaxWalkSpeed = GetRoleCharacterInfo()->GetCharacterMovement()->MaxWalkSpeed;
	GetRoleCharacterInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockWalkSpeed;
}

void UGA_TargetLock::ResetTargetLockMovement()
{
	GetRoleCharacterInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedMaxWalkSpeed;
}

void UGA_TargetLock::OnTargetLockTick(float DeltaTime)
{
	if (!CurrentLockedActor.IsValid())
	{
		CancelTargetLockAbility();
		return;
	}
	SetTargetLockWidgetPosition();
	const FRotator CurrentControlRot = GetRoleControllerFromActorInfo()->GetControlRotation();
	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetRoleCharacterInfo()->GetActorLocation(), CurrentLockedActor.Get()->GetActorLocation());
	LookAtRot -= FRotator(TargetLockCameraOffset, 0.f, 0.f);

	const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, RotateToTargetLockSpeed);
	GetRoleControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0));
	GetRoleCharacterInfo()->SetActorRotation(FRotator(0, TargetRot.Yaw, 0));
}

void UGA_TargetLock::OnSwitchTarget(FGameplayEventData Payload)
{
	GetAvailableTargetLockActors();
	TArray<AActor*> ActorsOnLeft;
	TArray<AActor*> ActorsOnRight;
	AActor* NewTargetToLock;
	GetAvailableActorsAroundCurrentLockedActor(ActorsOnLeft, ActorsOnRight);
	if (Payload.EventTag == WuwaGameplayTags::Player_Event_SwitchTargetLock_Left)
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnLeft);
	}
	else
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnRight);
	}
	if (NewTargetToLock)
	{
		CurrentLockedActor = NewTargetToLock;
	}
}

void UGA_TargetLock::GetAvailableActorsAroundCurrentLockedActor(TArray<AActor*>& ActorsOnLeft, TArray<AActor*>& ActorsOnRight)
{
	if (!CurrentLockedActor.IsValid() || AvailableActors.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}
	for (AActor* FoundActor : AvailableActors)
	{
		if (FoundActor == CurrentLockedActor)
		{
			continue;
		}
		const FVector ForwardVector = GetRoleCharacterInfo()->GetActorForwardVector();
		const FVector ToFoundActorVector = (FoundActor->GetActorLocation() - GetRoleCharacterInfo()->GetActorLocation()).GetSafeNormal();

		const FVector CrossResult = FVector::CrossProduct(ForwardVector, ToFoundActorVector);
		if (CrossResult.Z < 0)
		{
			ActorsOnLeft.AddUnique(FoundActor);
		}
		else
		{
			ActorsOnRight.AddUnique(FoundActor);
		}
	}
}

void UGA_TargetLock::DrawTargetLockWidget()
{
	if (TargetLockWidget == nullptr)
	{
		checkf(TargetLockWidgetClass, TEXT("Forget to assign Target Lock Widget"));
		TargetLockWidget = CreateWidget<UWuwaWidgetBase>(GetRoleControllerFromActorInfo(), TargetLockWidgetClass);
		check(TargetLockWidget);

		TargetLockWidget->AddToViewport();
	}
}


