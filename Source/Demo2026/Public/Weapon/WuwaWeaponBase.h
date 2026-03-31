// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Data/EnumTypes.h"
#include "WuwaWeaponBase.generated.h"

class UBoxComponent;

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate,AActor * )

UCLASS()
class DEMO2026_API AWuwaWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	virtual void BeginPlay() override;
	AWuwaWeaponBase();
	virtual void PostInitializeComponents() override;
	

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UBoxComponent* WeaponCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	EWeaponType WeaponType = EWeaponType::Weapon_None;


	virtual UMeshComponent* GetMesh();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, ReplicatedUsing = "OnRep_IsSkeletalMesh", Category = "Weapon")
	bool bIsSkeletalMesh = true;
	
	void ToggleWeaponCollision(ECollisionEnabled::Type CollisionType);

	FOnTargetInteractedDelegate OnWeaponHitTarget;
	FOnTargetInteractedDelegate OnWeaponPullFromTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
	bool bDrawCollisionBox = false;

	virtual void Tick(float DeltaTime)override;
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void HitActor(AActor* HitActor);
	FVector GetSocketLocation(FName SocketName);
protected:
	UFUNCTION()
	void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnRep_IsSkeletalMesh();
	
};
