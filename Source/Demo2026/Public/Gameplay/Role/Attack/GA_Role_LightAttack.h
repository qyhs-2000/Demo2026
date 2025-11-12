// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WuwaRoleGameplayAbility.h"
#include "GA_Role_LightAttack.generated.h"


class UAnimMontage;
class UAbilityTask_PlayMontageAndWait;
class AWuwaPlayerCharater;
/**
 * 
 */
UCLASS()
class DEMO2026_API UGA_Role_LightAttack : public UWuwaRoleGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Role_LightAttack();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Gameplay|Light Attack")
	TArray<UAnimMontage*> LightAttackMontages;

	UAbilityTask_PlayMontageAndWait* CurrentPlayTask;

	UFUNCTION()
	void PlayComboMontage();

	UFUNCTION()
	void OnMontageCompleted();

	UFUNCTION()
	void OnMontageInterrupted();

	UFUNCTION()
	void EndAttackComboAbility();

	UFUNCTION(NetMulticast,Reliable)
	void ResetCombo();

	UFUNCTION(Server, Reliable)
	void ServerResetCombo();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastResetCombo();

	void EnableComboInput();
	void TryContinueCombo();
	void OnInputPressed();
	void OnMoveInputReceived();

	void CancelAttack();
	void SetCanBeInterrupted(bool bCanInterrupted);

	UPROPERTY(ReplicatedUsing = OnRep_ReceiveInterrupted)
	bool bCanBeInterrupted = false;

	UFUNCTION()
	void OnRep_ReceiveInterrupted();

	UPROPERTY(Replicated)
	int32 AttackComboCount = 0;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server,Reliable,WithValidation)
	void Server_OnInputPressed();


	UFUNCTION(NetMulticast,Reliable)
	void MulticastPlayMontage(UAnimMontage* MontageToPlay);

	void PlayAnimMontage(UAnimMontage* MontageToPlay);
	
	UPROPERTY(Replicated)
	bool bComboInputAllowed = true;   // 是否允许提前输入

	UFUNCTION()
	bool Server_OnInputPressed_Validate();

	UFUNCTION()
	void Server_OnInputPressed_Implementation();

	bool CanActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags,
		const FGameplayTagContainer* TargetTags,
		FGameplayTagContainer* OptionalRelevantTags) const override;
private:
	UPROPERTY(Replicated)
	bool bComboQueued = false;         // 是否已提前按下
	
};
