// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorGameplayTags.h"

namespace WuwaGameplayTags
{
	/*Input Config*/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Role_Attack_Light, "InputTag.Role.Attack.Light");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Role_Attack_Heavy, "InputTag.Role.Attack.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Role_Dodge, "InputTag.Role.Dodge");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_TargetLock, "InputTag.Toggleable.TargetLock");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_SwitchTarget, "InputTag.SwitchTarget");

	/*Player Ability*/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack, "Player.Ability.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light, "Player.Ability.Attack.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy, "Player.Ability.Attack.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Dodge, "Player.Ability.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_SuperComputeMatrix, "Player.Ability.SuperComputeMatrix");


	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTargetLock, "Player.Event.SwitchTargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTargetLock_Left, "Player.Event.SwitchTargetLock.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTargetLock_Right, "Player.Event.SwitchTargetLock.Right");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_OnPerfectDodgeTrigger, "Player.Event.OnPerfectDodgeTrigger");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_TriggerSuperMatrix, "Player.Event.TriggerSuperMatrix");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_TargetLocking, "Player.Status.TargetLocking");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Dodging, "Player.Status.Dodging");

	UE_DEFINE_GAMEPLAY_TAG(Player_State_Cooldown_SuperMatrix, "Player.State.Cooldown.SuperMatrix");


	/*Enemy Tags*/
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");

	/*Shared*/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Invincible, "Shared.Status.Invincible");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death, "Shared.Status.Death");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_SpawnWeapon, "Shared.Ability.SpawnWeapon");

	/*Set By Caller*/
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");
}